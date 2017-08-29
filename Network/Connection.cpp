#include "Connection.h"


namespace Network {

	Connection::Connection()
	{
		_seq = 0;
	}

	Connection::Connection(Address address, uint32_t id) {
		_remoteAddress = address;
		_id = id;
		_state = CONNECTING;
	}


	Connection::~Connection()
	{
	}

}