#include "Address.h"

namespace Network {

	Address::Address()
	{
	}

	Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port) {
		_address = (a << 24) | (b << 16) | (c << 8) | d;
		_port = port;
	}

	Address::Address(unsigned int address, unsigned short port) {
		_address = address;
		_port = port;
	}

	unsigned int Address::getAddress() const {
		return _address;
	}

	unsigned char Address::getA() const {
		return _address >> 24;
	}

	unsigned char Address::getB() const {
		return (_address & (0xFF << 16)) >> 16;
	}

	unsigned char Address::getC() const {
		return (_address & (0xFF << 8)) >> 8;
	}

	unsigned char Address::getD() const {
		return _address & 0xFF;
	}

	unsigned short Address::getPort() const {
		return _port;
	}

}
