#pragma once

#include <stdint.h>

#include "common.h"
#include "Socket.h"

namespace Network {
	enum ConnState{CLOSED, CONNECTING, CONNECTED};

	class Connection
	{
	public:
		uint32_t _id;
		Address _remoteAddress;
		ConnState _state = CLOSED;
		ClSnapshot _frames[PACKET_BACKUP];

		uint32_t _seq;

		Connection();
		Connection(Address address, uint32_t id);
		~Connection();

	private:

	};

}