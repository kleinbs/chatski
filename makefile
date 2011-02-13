chatskiClient.o: chatskiClient.cpp
	g++ -c chatskiClient.cpp

chatskiClient: chatskiClient.o
	g++ chatskiClient.o -lncurses -o chatskiClient

all:	chatskiClient

clean:
	rm *.o chatskiClient
