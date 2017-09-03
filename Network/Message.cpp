#include "Message.h"

#include <cstring>

namespace Network {
	Message::Message() {
		_currsize = 0;
		_readIndex = 0;
	}


	Message::~Message() {
	}

	void Message::init(uint8_t *data, int size) {
		memcpy(_data, data, size);
	}

	uint32_t Message::readBits(int bits) {
		//not needed now
		return NULL;
	}

	uint8_t Message::readByte() {
		uint8_t ret;

		ret = _data[_readIndex];
		_readIndex += 1;
		return ret;
	}

	uint16_t Message::readShort() {
		uint16_t *ptr;

		ptr = (uint16_t *) &_data[_readIndex];
		_readIndex += 2;
		return *ptr;
	}

	uint32_t Message::readLong() {
		uint32_t *ptr;

		ptr = (uint32_t *) &_data[_readIndex];
		_readIndex += 4;
		return *ptr;
	}

	int Message::readInt() {
		int ret;

		ret = *(int *) &_data[_readIndex];
		_readIndex += 4;
		return ret;
	}

	void Message::writeBits(int data, int bits) {
		//not needed right now
	}

	void Message::writeByte(uint8_t data) {
		_data[_currsize] = data;

		_currsize += 1;
	}

	void Message::writeShort(uint16_t data) {
		uint16_t *ptr = (uint16_t *) &_data[_currsize];
		*ptr = data;

		_currsize += 2;
	}

	void Message::writeLong(uint32_t data) {
		uint32_t *ptr = (uint32_t *) &_data[_currsize];
		*ptr = data;

		_currsize += 4;
	}

	void Message::writeInt(int data) {
		int *ptr = (int *) (&_data[_currsize]);
		*ptr = data;

		_currsize += 4;
	}
}
