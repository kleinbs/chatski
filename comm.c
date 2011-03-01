#include <stdio.h>
#include <stdlib.h>

#define MAXPENDING 5

void DieWithError( char *errorMessage );

void comm(int sockfd) {
    
    if( listen( sockfd, MAXPENDING ) < 0 )
		fprintf(stderr, "socket() failed on %i\n", sockfd);
    
   while(1)
    {
      //printf("i'm working");
    }
    
    exit(1);
} 
