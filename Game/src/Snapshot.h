#pragma once

#include <vector>
#include "entities/entity.h"

class Snapshot
{
public:
	Snapshot();
	~Snapshot();

	std::vector<Entity> entities;
};

