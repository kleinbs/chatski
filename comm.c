#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipeStructs.c"

#define MAXPENDING 5

void DieWithError( char *errorMessage );

void comm(void* p) {
  
   int n, nbytes;;
   char buffer[256];
   bzero(buffer,256);
   
   struct sock_pipe foo = *((struct sock_pipe*)(p)); 
   
   printf("establishing connection on socket %d\n", foo.sock);
    
   while(1)
    {
     n = read(foo.sock,buffer,255);
     if (n < 0) 
       printf("ERROR reading from socket");
     write(foo.talkPipe, foo.sock, sizeof(buffer));
     nbytes = read(foo.listenPipe, buffer, sizeof(buffer));
     printf("Here is the message on socket %d: %s\n", buffer, foo.sock);
     n = write(nbytes,"I got your message",18);
     if (n < 0) 
       printf("ERROR writing to socket");
    }
    
    exit(1);
} 
