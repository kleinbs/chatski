// Chatski Server
// more changes
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5;
#define SERVSOCK 90;

void DieWithError(char *errorMessage);

int sockArr[10];

int main(int argc, char *argv[])
{
 for(;;)
 {
  if(listen(SERVSOCK, MAXPENDING) < 0)
	dieWithError("listen() failed");
 }	
}
