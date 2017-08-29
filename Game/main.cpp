#include <iostream>

#include <MattEngine/window.h>
#include "game.h"


int main() {

	Game mainGame = Game("My Game", 800, 600);
	mainGame.run();


	std::cout << "Game Ended" << std::endl;

	////network memes
	//Network::Socket sock;
	//Network::Connection connection;
	//sock.open(5001);

	//Network::Address destAddr(127, 0, 0, 1, 5000);

	//unsigned char message[256];
	//int bp = 0;

	////generate packet header and return index to add data
	//bp = sock.generateHeader(message, 69420, NULL, NULL, SYN);

	////adding data to packet
	//printf("%d", bp);
	//const int dataSize = 4;
	//unsigned char data[dataSize];
	//((unsigned int*)data)[0] = 69;

	//memcpy((message + bp), data, sizeof(data));
	//
	////send packet
	//sock.send(destAddr, message, sizeof(message));

	//bp = sock.generateHeader(message, 69420, 1, 0, ACK);
	//sock.send(destAddr, message, sizeof(message));

	return 0;
}