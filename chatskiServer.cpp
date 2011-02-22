// Chatski Server
// more changes
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5;
#define SERVERPORT 90;

void DieWithError(char *errorMessage);

int sockArr[10];

int main(int argc, char *argv[])
{

 int servSock;
 int clntSock;
 struct sockaddr_in echoServAddr;
 struct sockaddr_in echoClntAddr;
 unsigned int clntLen;

//assign the servert socket
 if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	dieWithError("socket() failed");

//Create the local address structure
memset(&echoServAddr, 0, sizeof(echoServAddr));
echoServAddr.sin_family = AF_INET;
echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
echoServAddr.sin_port = htons(echoServPort);

if(bind(servSock, (struct sockaddr *), &echoServAddr, sizeOf(echoServAddr)) < 0)
	dieWithError("bind() failed");

 for(;;)
 {
  if(listen(servSock, MAXPENDING) < 0)
	dieWithError("listen() failed");
 }

}	
