#include "Server.h"

Server::Server(int port)
{
	_port = port;
}


Server::~Server()
{
}

void Server::init() {
	_connClients = 0;
	_gameTime = 0;

	_numSnapshots = LOBBY_SIZE * PACKET_BACKUP * MAX_ENTITIES;
	_entSnapshots = new EntityState[_numSnapshots];
	_snapshotIndex = 0;

	_sock.open(_port);
	_state = sv_state::SV_CONNECTING;
}

void Server::run() {
	double deltaTime = 0.0f;
	clock_t currTime;
	clock_t timer = clock();
	clock_t lastTime = timer;
	int frames = 0;
	int updates = 0;

	double ups = 60.0;
	double period = 1.0 / UPDATES_PER_SEC;

	printf("Receiving ...\n");
	while (true) {
		currTime = clock();
		deltaTime += currTime - lastTime;

		receive();

		if (deltaTime > period * (double)CLOCKS_PER_SEC) {
			//game tick
			updates++;
			deltaTime = deltaTime - period * (double)CLOCKS_PER_SEC;

			//
			//NEW
			//
			//create snapshot and send to each client
			for (auto client : _clients) {
				buildSnapshot(client.second);

				sendSnapshot(client.second);
			}

			//
			//OLD
			//
			//create packet
			uint8_t message[256];
			int bp;
			bp = _sock.generateHeader(message, 69420, 1, 0, 0);
		}

		lastTime = currTime;

		if (clock() - timer > 5 * (double)CLOCKS_PER_SEC) {
			timer += 5 * (double)CLOCKS_PER_SEC;
			//printf( "%d updates per sec\n", (updates / 5));
			updates = 0;
		}
	}
}

void Server::buildSnapshot(Network::Connection &client) {
	ClSnapshot *frame;
	frame = &client._frames[client._seq % PACKET_BACKUP];

	//just adding all the entities currently, could selectively send entities for security
	/* NOTE: would be faster to currenty do just one build for all clients, but keeping it this
	         way for when clients are shown data selectively */
	frame->numEntities = 0;
	frame->start = _snapshotIndex;
	EntityState *state;
	for (int i = 0; i < _entities.size(); i++) {
		_entSnapshots[_snapshotIndex % _numSnapshots] = _entities.at(i)->getState();

		_snapshotIndex++;
		frame->numEntities++;
	}

}

void Server::sendSnapshot(Network::Connection &client) {
	Network::Message msg;

	//Sequence Number

}

void Server::receive() {
	//receive packets
	while (true) {

		Network::Address sender;
		uint8_t buffer[256];
		int bytesRead = _sock.receive(sender, buffer, sizeof(buffer));

		if (bytesRead <= 0) {
			break;
		}

		Network::Message msg;
		msg.init(buffer, bytesRead);

		printf("message from %d.%d.%d.%d:%d: %x\n", sender.getA(),
			sender.getB(),
			sender.getC(),
			sender.getD(),
			sender.getPort(),
			msg._data);

		//packet header
		uint32_t protID = msg.readLong();
		uint32_t seq = msg.readLong();
		uint16_t connID = msg.readShort();
		uint8_t flags = msg.readByte();

		printf("Protocol ID: %d\n", protID);
		if (protID != 69420) {
			printf("wrong Protocol ID, dropping packet...\n");
		}
		else {
			//process packet
			switch (_state) {
                case sv_state::SV_CONNECTING: {
                    printf("got here\n");
					if (flags & SYN) {
						printf("connection establishing\n");
						int id = _clients.size() + 1;
						printf("id: %d\n", id);
						Network::Connection connection(sender, id);
						_clients.insert(std::make_pair(id, connection));

						//send SYN/ACK
						Network::Message sendMsg;
						sendMsg.writeLong(1);
						sendMsg.writeShort(connection._id);
						sendMsg.writeByte(SYN | ACK);
						printf("sending SYN/ACK\n");
						_sock.send(connection._remoteAddress, sendMsg._data, sizeof(sendMsg._data));
					}
					else {
						printf("connID: %d\n", connID);
						auto it = _clients.find(connID);
						if (it != _clients.end()) {
                            printf("same client\n");
							if (flags & ACK) {
								printf("connection established\n");
								it->second._state = Network::ConnState::CONNECTED;
								_connClients++;
							}
						}
					}

					//check for full lobby
					if (_connClients == LOBBY_SIZE) {
						int count = 0;
						//intialize players and drop unconnected clients
						for (auto it : _clients) {
							if (it.second._state == Network::ConnState::CONNECTED) {
								//connected client
								_entities.push_back(new Player(0, (-50 + 100 * count), 1));
							}
							else {
								//unconnected client
								_clients.erase(it.first);
							}
						}
						//start game
						printf("starting game...\n");
						_state = sv_state::SV_PLAY;
						_gameTime = 0;

						//creategamestate msg
						for (auto it : _clients) {
                            printf("sending gamestate\n");
							Network::Message sendMsg;
							sendMsg.writeLong(it.second._seq);
							sendMsg.writeLong(it.second._ack);
							sendMsg.writeByte(scmd_GameState);
							sendMsg.writeByte(_state);
							sendMsg.writeByte(scmd_EOF);
							_sock.send(it.second._remoteAddress, sendMsg._data, sendMsg._currsize);
						}
					}
					break;
				}
                case sv_state::SV_PLAY: {
                    //do things
                    break;
                }
			}
			//handle data
			//printf("%d xD\n", *(unsigned int*)(buffer + sizeof(header)));

		}
	}

}

void Server::broadcast(Network::Message msg) {
    for(auto it : _clients) {
		_sock.send(it.second._remoteAddress, msg._data, msg._currsize);
	}
}
