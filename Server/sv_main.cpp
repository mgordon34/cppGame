#include <iostream>
#include <ctime>
#include <unordered_map>

#include <Network/Socket.h>
#include <Network/Connection.h>

#include "entity.h"
#include "Player.h"
#include "Server.h"


int main() {
	Server server(5000);
	server.init();
	server.run();

}
