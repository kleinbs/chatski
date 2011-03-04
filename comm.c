#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXPENDING 5

void DieWithError( char *errorMessage );

void comm(int sock) {
  
   int n;
   char buffer[256];
      
   bzero(buffer,256);
   
   printf("establishing connection on socket %d\n", sock);
    
   while(1)
    {
     n = read(sock,buffer,255);
     if (n < 0) 
       printf("ERROR reading from socket");
     printf("Here is the message on socket %d: %s\n", sock, buffer);
     n = write(sock,"I got your message",18);
     if (n < 0) 
       printf("ERROR writing to socket");
    }
    
    exit(1);
} 
