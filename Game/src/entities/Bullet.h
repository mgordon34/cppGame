#pragma once

#include <MattEngine/SpriteBatch.h>

#include "entity.h"

#define BULLET_WIDTH 50
#define BULLET_HEIGHT 50

class Bullet : public Entity
{
public:
	Bullet(float x, float y, uint16_t id, glm::vec2 dir, float speed);
	~Bullet();

	void update();
	void draw(MattEngine::SpriteBatch &sb);

private:
	float _speed;
	glm::vec2 _dir;
};

