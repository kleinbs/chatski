#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5

void DieWithError( char *errorMessage );
void HandleTCPClient( int clntSocket);

int main( int argc, char *argv[] ) {
	int servSock;
	int clntSock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	unsigned short echoServPort;
	unsigned int clntLen;

	if( argc != 2 ) {
		fprintf( stderr, "Usage: %s <Server Port>\n", argv[0] );
		exit( 1 );
	}

	echoServPort = atoi( argv[1] );

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

		HandleTCPClient( clntSock );
	}
	/* NOT REACHED */
}
