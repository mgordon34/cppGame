#pragma once

#include <MattEngine/SpriteBatch.h>

class Entity {

public:
	Entity(float x, float y, uint16_t id);

	virtual void update();
	virtual void draw(MattEngine::SpriteBatch &sb);

protected:
	uint16_t _id;
	GLuint _tex;

	glm::vec2 _pos;
    int _width;
	int _height;
};

