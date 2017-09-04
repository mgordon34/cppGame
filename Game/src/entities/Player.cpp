#include <MattEngine/ResourceManager.h>
#include "Player.h"

Player::Player(float x, float y, uint16_t id) : Entity(x, y, id)
{
    _tex = MattEngine::ResourceManager::getTexture("res/xd.png");

    _width = PLAYER_WIDTH;
    _height = PLAYER_HEIGHT;
}


Player::~Player()
{
}

void Player::update() {
    _pos += _dir * _speed;
}

//void Player::draw(MattEngine::SpriteBatch &sb) {
//}
