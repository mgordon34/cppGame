#pragma once

#include <Network/common.h>

class Entity {

public:
	Entity(float x, float y, uint16_t id);

	virtual void update();

	virtual EntityState getState();

protected:
	glm::vec2 _pos;
	uint16_t _id;
};

