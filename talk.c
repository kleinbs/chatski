#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "pipeStructs.c"

#define MAXPENDING 5

void talk(void* p) {
  
  char    readbuffer[80];
  int     nbytes;
  struct pipes foo = *((struct pipes*)(p)); 
  
  while(1)
  {
    nbytes = read(foo.listenPipe, readbuffer, sizeof(readbuffer));
    if(nbytes <= 0)
      write(foo.talkPipe, readbuffer, sizeof(readbuffer));
  } 
}
  