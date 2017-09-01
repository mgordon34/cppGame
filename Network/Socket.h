#pragma once

#include "Address.h"
#include <stdint.h>

#define SYN 0x1
#define ACK 0x2

namespace Network {

	struct Header {
		uint32_t protocolID;
		uint32_t sequenceNum;
		uint16_t connectionID;
		uint8_t flags;
	};

	class Socket
	{
	public:
		Socket();
		~Socket();

		bool open(unsigned short port);
		void sock_close();
		bool isOpen() const;

		int generateHeader(unsigned char *buffer, uint32_t protID, uint32_t seqNum, uint16_t connID, uint8_t flags);
		bool send(const Address &dest, const void *data, int size);
		bool sendAck(const Address &dest, uint32_t protID, uint16_t connID);
		int receive(Address &sender, void *data, int size);

	private:
		int _sock;
	};

}

