#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

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
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned short echoServPort = 99;
	unsigned int clntLen;
	pthread_t thread;
	int  iret, msgHandler;
	
	printf("I am running!!\n");
	/* Create socket for incoming connections */
	if( ( servSock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP ) ) < 0 )
		DieWithError( "socket() failed" );

	/* Construct local address structure */
	memset( &echoServAddr, 0, sizeof( echoServAddr ) );
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = htonl( INADDR_ANY );
	echoServAddr.sin_port = htons( echoServPort );

	/* Bind to the local address */
	if( bind( servSock, ( struct sockaddr * ) &echoServAddr, sizeof( echoServAddr ) ) < 0 )
		DieWithError( "bind() failed" );

	/* Mark the socket so it will listen for incoming connections */
	if( listen( servSock, MAXPENDING ) < 0 )
		DieWithError( "listen() failed" );

	for( ;; ) {
		/* Set the size of the in-out parameter */
		clntLen = sizeof( echoClntAddr );
		
		/* Wait for a client to connect */
		if( ( clntSock = accept( servSock, ( struct sockaddr * ) &echoClntAddr, &clntLen ) ) < 0 )
			DieWithError( "accept() failed" );
		
		/* clntSock is connected to a client */
		printf( "Handling client %s\n", inet_ntoa( echoClntAddr.sin_addr ) );
		
		iret = pthread_create( &thread, NULL, comm, (void*) clntSock);
		threads[count] = iret;
		count++;
		//close(clntSock);
		
	}
	/* NOT REACHED */
}

