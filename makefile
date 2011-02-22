chatskiClient.o: chatskiClient.cpp
	g++ -c chatskiClient.cpp
	g++ -c chatskiServer.cpp
	g++ -c DieWithError.cpp
chatskiClient: chatskiClient.o
	g++ chatskiClient.o -lncurses -o chatskiClient
chatskiServer: chatskiServer.o	
	g++ chatskiServer.o DieWithError.o -o chatskiServer
DieWithError: DieWithError.o
	g++ DieWithError.o -o DieWithError
all:	chatskiClient chatskiServer DieWithError

clean:
	rm *.o chatskiClient
	rm *.o chatskiServer
	rm *.o DieWithError
