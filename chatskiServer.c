#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "pipeStructs.c"

#define MAXPENDING 5


void DieWithError( char *errorMessage );
void comm( int sockfd );
//void HandleTCPClient( int clntSocket);

int threads[50];

int main( int argc, char *argv[] ) {
	int servSock;
	int clntSock;
	int pid;
	int count = 0;
	int thread_server[2], server_thread[2];
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	struct pipes t;
	struct sock_pipe c;
	unsigned short echoServPort = 99;
	unsigned int clntLen;
	pthread_t thread;
	int  iret, talk, msgHandler;
	
	printf("I am running!!\n");
	/* Create socket for incoming connections */
	if( ( servSock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP ) ) < 0 )
		DieWithError( "socket() failed" );
	
	printf("created server socket\n");
	
	/* Create the needed pipes */
	pipe(thread_server);
	pipe(server_thread);
	
	t.listenPipe = thread_server[1];
	t.talkPipe = server_thread[0];
	
	/* Create the talk thread to listen for messages */
	talk = pthread_create( &thread, NULL, talk, (void*) &t);
	
	//printf("created talk thread\n");

	/* Construct local address structure */
	memset( &echoServAddr, 0, sizeof( echoServAddr ) );
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl( INADDR_ANY );
	echoServAddr.sin_port = htons( echoServPort );
	
	printf("work to here");

	/* Bind to the local address */
	if( bind( servSock, ( struct sockaddr * ) &echoServAddr, sizeof( echoServAddr ) ) < 0 )
		DieWithError( "bind() failed" );
	
	/* Mark the socket so it will listen for incoming connections */
	if( listen( servSock, MAXPENDING ) < 0 )
		DieWithError( "listen() failed" );
	
	printf("got to for loop\n");

	for( ;; ) {
		/* Set the size of the in-out parameter */
		clntLen = sizeof( echoClntAddr );
		
		printf("work to here 1\n");
		
		/* Wait for a client to connect */
		if( ( clntSock = accept( servSock, ( struct sockaddr * ) &echoClntAddr, &clntLen ) ) < 0 )
			DieWithError( "accept() failed" );
		
		/* clntSock is connected to a client */
		printf( "Handling client %s\n", inet_ntoa( echoClntAddr.sin_addr ) );
		
		c.sock = clntSock;
		c.listenPipe = server_thread[1];
		c.talkPipe = thread_server[0];
		printf("work to here\n");
		iret = pthread_create( &thread, NULL, comm, (void*) &c);
		threads[count] = iret;
		count++;
		//close(clntSock);
		printf("am i still working?\n");
	}
	/* NOT REACHED */
}

