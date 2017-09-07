#include <MattEngine/ResourceManager.h>
#include "Player.h"

Player::Player(float x, float y, uint16_t id) : Entity(x, y, id, PLAYER_WIDTH, PLAYER_HEIGHT, "res/xd.png")
{
}


Player::~Player()
{
}

void Player::update() {
    _pos += _dir * _speed;
}

//void Player::draw(MattEngine::SpriteBatch &sb) {
//}
