#pragma once

namespace Network {

	class Address
	{
	public:
		Address();
		Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
		Address(unsigned int address, unsigned short port);

		unsigned int getAddress() const;
		unsigned char getA() const;
		unsigned char getB() const;
		unsigned char getC() const;
		unsigned char getD() const;
		unsigned short getPort() const;

	private:
		unsigned int _address;
		unsigned short _port;
	};

}
