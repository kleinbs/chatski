#include <stdio.h>
#include <stdlib.h>

#define MAXPENDING 5

void DieWithError( char *errorMessage );

void comm(int sockfd) {
    if( listen( sockfd, MAXPENDING ) < 0 )
		DieWithError( "listen() failed on socket " + sockfd);
    
    
    
    exit(1);
} 
