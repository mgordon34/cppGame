#include "entity.h"

Entity::Entity(float x, float y, uint16_t id) {
	_pos = glm::vec2(x, y);
	_id = id;
}

void Entity::update() {

}

EntityState Entity::getState() {
	EntityState state;
	
	state.id = _id;
	state.type = 0;
	state.xPos = _pos.x;
	state.yPos = _pos.y;

	return state;
}