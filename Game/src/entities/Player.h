#pragma once

#include <glm/glm.hpp>

#include "entity.h"

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100

class Player : public Entity
{
public:
	Player(float x, float y, uint16_t id);
	~Player();

	void update();
	void draw(MattEngine::SpriteBatch &sb);

private:
	int health;
	float _speed;
	glm::vec2 _dir;
};

