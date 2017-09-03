#pragma once

#include <vector>
#include <unordered_map>
#include <ctime>

#include <Network/common.h>
#include <Network/Address.h>
#include <Network/Connection.h>
#include <Network/Socket.h>
#include <Network/Message.h>

#include "entity.h"
#include "Player.h"

#define UPDATES_PER_SEC 30

#define LOBBY_SIZE 2
#define MAX_ENTITIES 32


enum sv_state { CONNECTING, PRE_GAME, PLAY, END };

class Server
{
public:
	Server(int port);
	~Server();

	void init();
	void run();

	void receive();
    void broadcast(Network::Message msg);

	void buildSnapshot(Network::Connection &client);
	void sendSnapshot(Network::Connection &client);

private:
	int _port;
	Network::Socket _sock;
	sv_state _state;

	std::unordered_map<int, Network::Connection> _clients;
	std::vector<Entity *> _entities;

	EntityState *_entSnapshots;  //master list of all entity data
	int _numSnapshots;  //number of entries allowed in _entSnapshots
	int _snapshotIndex;  //current index of next EntityState to be written in _entSnapshots

	int _connClients;
	int _gameTime;
};

