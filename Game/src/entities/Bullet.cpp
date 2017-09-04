#include "Bullet.h"

#include <MattEngine/ResourceManager.h>


Bullet::Bullet(float x, float y, uint16_t id, glm::vec2 dir, float speed) : Entity(x, y, id)
{
	_tex = MattEngine::ResourceManager::getTexture("res/xd.png");

	_width = BULLET_WIDTH;
	_height = BULLET_HEIGHT;
	_dir = dir;
	_speed = speed;
}


Bullet::~Bullet()
{
}

void Bullet::update() {
	_pos += _dir * _speed;
}

//void Bullet::draw(MattEngine::SpriteBatch &sb) {
//}
