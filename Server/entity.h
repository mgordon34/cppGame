#pragma once

#include <MattEngine/SpriteBatch.h>
#include <Network/common.h>

class Entity {

public:
	Entity(float x, float y, uint16_t id);

	virtual void update();
	virtual void draw(MattEngine::SpriteBatch &sb);

	virtual EntityState getState();

protected:
	glm::vec2 _pos;
	uint16_t _id;
};

