#pragma once

#include <stdint.h>

namespace Network {
	class Message {
	public:
		int _currsize;
		uint8_t _data[256];

		Message();

		~Message();

		void init(uint8_t *data, int size);

		uint32_t readBits(int bits);

		uint8_t readByte();

		uint16_t readShort();

		uint32_t readLong();

		int readInt();

		void writeBits(int data, int bits);

		void writeByte(uint8_t data);

		void writeShort(uint16_t data);

		void writeLong(uint32_t data);

		void writeInt(int data);

	private:
		int _readIndex;

	};

}

