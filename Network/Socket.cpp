#include "Socket.h"

#include <iostream>

//Socket definition memes
#define PLAT_WINDOWS 0
#define PLAT_MAC 1
#define PLAT_LINUX 2

#if defined(_WIN32)
#define PLATFORM PLAT_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLAT_WINDOWS
#else
#define PLATFORM PLAT_WINDOWS
#endif

#if PLATFORM == PLAT_WINDOWS
#include <WinSock2.h>
#pragma comment( lib, "wsock32.lib" )
#elif PLATFORM == PLAT_MAC || PLATFORM == PLAT_LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif

namespace Network {

	Socket::Socket()
	{
#if PLATFORM == PLAT_WINDOWS
		WSADATA WsaData;
		bool result = WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
		if (!result) {
			printf("faild to initialize\n");
		}
#endif

		//create socket
		_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (_sock <= 0) {
			printf("socket failed bitch\n");
		}
	}


	Socket::~Socket()
	{
#if PLATFORM == PLAT_WINDOWS
		WSACleanup();
#endif
	}

	bool Socket::open(unsigned short port) {
		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons((unsigned short)port);

		if (bind(_sock, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0) {
			printf("socket failed to bind bitch\n");
			return 0;
		}

		//set to non-blocking mode
#if PLATFORM == PLAT_WINDOWS
		DWORD nonBlocking = 1;
		if (ioctlsocket(_sock, FIONBIO, &nonBlocking) != 0) {
			printf("failed to set non-blocking bitch\n");
			return 0;
		}
#elif PLATFORM == PLAT_MAC || PLATFORM == PLAT_LINUX
		int nonBlocking = 1;
		if (fcntl(_sock, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
			printf("failed to set non-blocking bitch\n");
			return 0;
		}
#endif
		return true;
	}
	void Socket::close() {
#if PLATFORM == PLAT_MAC || PLATFORM == PLAT_LINUX
		close(_sock);
#elif PLATFORM == PLAT_WINDOWS
		closesocket(_sock);
#endif
	}

	bool Socket::isOpen() const {
		//TODO
		return true;
	}

	int Socket::generateHeader(unsigned char *buffer, uint32_t protID, uint32_t seqNum, uint16_t connID, uint8_t flags) {
		Header header;
		//ProtocolID
		header.protocolID = protID;
		header.sequenceNum = seqNum;
		header.connectionID = connID;
		header.flags = flags;

		memcpy(buffer, &header, sizeof(header));
		return sizeof(header);
	}

	bool Socket::send(const Address &dest, const void *data, int size) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(dest.getAddress());
		addr.sin_port = htons(dest.getPort());

		int sentBytes = sendto(_sock, (const char*)data, size, 0, (sockaddr*)&addr, sizeof(sockaddr_in));
		if (sentBytes != size) {
			printf("failed to send packet bitch\n");
			return false;
		}
		return true;
	}

	bool Socket::sendAck(const Address &dest, uint32_t protID, uint16_t connID) {
		uint8_t message[256];
		int bp;
		bp = generateHeader(message, 69420, 1, connID, ACK);
		printf("sending ACK\n");
		return send(dest, message, bp);
	}

	int Socket::receive(Address &sender, void *data, int size) {

#if PLATFORM == PLAT_WINDOWS
		typedef int socklen_t;
#endif
		sockaddr_in from;
		socklen_t fromLength = sizeof(from);

		int bytesRead = recvfrom(_sock, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

		unsigned int fromAddr = ntohl(from.sin_addr.s_addr);
		unsigned int fromPort = ntohs(from.sin_port);
		sender = Address(fromAddr, fromPort);

		return bytesRead;
	}

}