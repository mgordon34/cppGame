#include <MattEngine/ResourceManager.h>
#include "Player.h"

Player::Player(float x, float y, uint16_t id) : Entity(x, y, id)
{
    _tex = MattEngine::ResourceManager::getTexture("res/xd.png");
}


Player::~Player()
{
}

void Player::update() {
    _pos += _dir * _speed;
}

void Player::draw(MattEngine::SpriteBatch &sb) {
    glm::vec4 pos = glm::vec4(_pos.x, _pos.y, PLAYER_WIDTH, PLAYER_HEIGHT);
    glm::vec4 uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    MattEngine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    sb.draw(pos, uv, _tex, 0.0f, color);
}
