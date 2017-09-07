#pragma once

#include <MattEngine/window.h>
#include <MattEngine/InputManager.h>
#include <MattEngine/GLSLProgram.h>
#include <MattEngine/Camera2D.h>
#include <MattEngine/SpriteBatch.h>

#include <Network/Socket.h>
#include <Network/Connection.h>

#include <MattEngine/sprite.h>
#include <Game/src/entities/Player.h>
#include <Game/src/Menu.h>
#include "src/entities/entity.h"
#include "src/entities/Bullet.h"

class Game
{
public:
	Game(const char *name, int width, int height);
	~Game();

	void run();

	void gameLoop();
	void processInputs();
	void update();
	void render();

private:
	MattEngine::Window _window;
	cl_state _gameState;
	MattEngine::InputManager *_inputManager;
	MattEngine::GLSLProgram _colorProgram;
	MattEngine::Camera2D _camera;
	MattEngine::SpriteBatch _spriteBatch;

	Network::Socket _socket;
	Network::Address _address;
	Network::Connection _connection;

	int _width, _height;
	const char *_name;
	float _time;

    Player *player = 0;

	Menu _menu;

	std::vector<MattEngine::Sprite *> _sprites;
	std::vector<Entity *> _bullets;
	std::vector<Entity *> _entities;

	void init();
	void initShaders();

};

