#pragma once

#include <glm/glm.hpp>

#include "entity.h"

class Player : public Entity
{
public:
	Player(float x, float y, uint16_t id);
	~Player();

};

