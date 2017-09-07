#include <MattEngine/ResourceManager.h>
#include "entity.h"

Entity::Entity(float x, float y, uint16_t id) {
    Entity(x, y, id, 0, 0, "");
}

Entity::Entity(float x, float y, uint16_t id, int width, int height, const char *tex) {
	_pos = glm::vec2(x, y);
	_id = id;
	_tex = MattEngine::ResourceManager::getTexture(tex);
    _width = width;
	_height = height;
}

void Entity::update() {

}

void Entity::draw(MattEngine::SpriteBatch &sb) {
	glm::vec4 pos = glm::vec4(_pos.x, _pos.y, _width, _height);
	glm::vec4 uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	MattEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	sb.draw(pos, uv, _tex, 0.0f, color);
}