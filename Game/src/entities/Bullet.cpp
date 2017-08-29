#include "Bullet.h"

#include <MattEngine/ResourceManager.h>


Bullet::Bullet(float x, float y, uint16_t id, glm::vec2 dir, float speed) : Entity(x, y, id)
{
	_dir = dir;
	_speed = speed;
}


Bullet::~Bullet()
{
}

void Bullet::update() {
	_pos += _dir * _speed;
}

void Bullet::draw(MattEngine::SpriteBatch &sb) {
	glm::vec4 pos = glm::vec4(_pos.x, _pos.y, 50, 50);
	glm::vec4 uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	MattEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	static GLuint tex = MattEngine::ResourceManager::getTexture("res/xd.png");

	sb.draw(pos, uv, tex, 0.0f, color);
}
