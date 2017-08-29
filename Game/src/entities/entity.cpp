#include "entity.h"

Entity::Entity(float x, float y, uint16_t id) {
	_pos = glm::vec2(x, y);
	_id = id;
}

void Entity::update() {

}

void Entity::draw(MattEngine::SpriteBatch &sb) {
	printf("this ran\n");
}