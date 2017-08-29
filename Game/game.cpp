#include "game.h"

#include <MattEngine\ImageLoader.h>
#include <MattEngine\ResourceManager.h>

#include <Network/Message.h>

#define Updates_Per_Second 60

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	MattEngine::InputManager *im = MattEngine::InputManager::getInstance();
	if (action == GLFW_PRESS) {
		im->pressKey(key);
	}
	else if (action == GLFW_RELEASE) {
		im->releaseKey(key);
	}
}

void mouseButtonCallback(GLFWwindow *window, int key, int action, int mods) {
	MattEngine::InputManager *im = MattEngine::InputManager::getInstance();
	if (action == GLFW_PRESS) {
		im->pressKey(key);
	}
	else if (action == GLFW_RELEASE) {
		im->releaseKey(key);
	}
}

void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
	MattEngine::InputManager *im = MattEngine::InputManager::getInstance();
	im->setMouseCoords(xPos, yPos);
}

Game::Game(const char *name, int width, int height)
{
	_name = name;
	_width = width;
	_height = height;
	_gameState = GameState::PLAY;
	_camera.init(_width, _height);

	//network memes
	_socket.open(0);
	_address = Network::Address(127, 0, 0, 1, 5000);
	//TEMP
	_gameState = GameState::CONNECTING;
}

Game::~Game()
{
	for (int i = 0; i < _bullets.size(); i++) {
		delete(_bullets[i]);
	}
}

void Game::run() {
	init();

	gameLoop();
}

void Game::init() {
	int result = _window.init(_name, _width, _height);
	if (result) {
		std::cout << "shit happened with window init" << std::endl;
	}

	initShaders();
	glfwSetKeyCallback(_window.getWindow(), key_callback);
	glfwSetMouseButtonCallback(_window.getWindow(), mouseButtonCallback);
	glfwSetCursorPosCallback(_window.getWindow(), cursorPositionCallback);

	_inputManager = MattEngine::InputManager::getInstance();
	_spriteBatch.init();

	//SpriteSheet _spritesheet = SpriteSheet("res/xd2.png");

	MattEngine::Sprite * player = new MattEngine::Sprite(&_window);
	MattEngine::Sprite * newplayer = new MattEngine::Sprite(&_window);

	//GLuint texID = _spritesheet.getTexID();
	//Entity * entity = new Entity(this);
	//player->loadpng("res/xd2.png");
	player->init(MattEngine::makeVector2(0, 0), 100, 100, "res/xd.png");
	newplayer->init(MattEngine::makeVector2(100, 100), 100, 100, "res/xd.png");
	//entity->init(makeVector2(50, 50), 100, 100, texID);

	//_tex = ImageLoader::loadPicture("res/xd.png");

	_sprites.push_back(player);
	_sprites.push_back(newplayer);
	//_sprites.push_back(entity);
}

void Game::initShaders() {
	_colorProgram.compileShaders("shaders/colorShading.vert.txt", "shaders/colorShading.frag.txt");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void Game::gameLoop() {
	double deltaTime = 0.0f;
	double currTime;
	double timer = glfwGetTime();
	double lastTime = glfwGetTime();
	int frames = 0;
	int updates = 0;

	double ups = 60.0;
	double period = 1.0 / Updates_Per_Second;
	double fps = period * ups;

	while (_gameState != GameState::EXIT && !_window.closed()) {
		currTime = glfwGetTime();
		deltaTime += currTime - lastTime;	

		if (deltaTime > period) {
			glfwPollEvents();
			glfwGetFramebufferSize(_window.getWindow(), &_width, &_height);

			processInputs();
			_inputManager->update();

			_camera.update();
			update();

			updates++;
			deltaTime = deltaTime - period;
		}

		frames++;
		render();

		lastTime = currTime;

		if (glfwGetTime() - timer > 5) {
			timer += 5.0f;
			std::printf("%d FPS, %d tickrate\n", frames / 5, updates / 5);
			frames = 0;
			updates = 0;
		}

	}
}

void Game::processInputs() {
	float scaleSpeed = 0.05f;
	float cameraSpeed = 1.0f;

	if (_inputManager->isKeyDown(GLFW_KEY_UP)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, cameraSpeed));
	}
	if (_inputManager->isKeyDown(GLFW_KEY_DOWN)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -cameraSpeed));
	}
	if (_inputManager->isKeyDown(GLFW_KEY_LEFT)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-cameraSpeed, 0.0));
	}
	if (_inputManager->isKeyDown(GLFW_KEY_RIGHT)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(cameraSpeed, 0.0));
	}
	if (_inputManager->isKeyDown(GLFW_KEY_Q)) {
		_camera.setScale(_camera.getScale() - scaleSpeed);
	}
	if (_inputManager->isKeyDown(GLFW_KEY_E)) {
		_camera.setScale(_camera.getScale() + scaleSpeed);
	}
	if (_inputManager->isKeyPressed(GLFW_MOUSE_BUTTON_1)) {
		glm::vec2 coords = _inputManager->getMouseCoords();
		coords = _camera.convertScreenToWorld(coords);
		_bullets.push_back(new Bullet(0, 0, _bullets.size(), glm::normalize(coords - glm::vec2(0,0)), 2));
	}
}

void Game::update() {
	_time += 0.1;

	switch (_gameState) {
	case GameState::CONNECTING:
		if (_connection._state == Network::ConnState::CLOSED) {
			Message msg;
			msg.writeLong(69420);
			msg.writeLong(0);
			msg.writeShort(0);
			msg.writeByte(SYN);

			_socket.send(_address, msg._data, sizeof(msg._data));
			_connection._state = Network::ConnState::CONNECTING;
			printf("sent SYN\n");
		}
		break;
	}

	//receive memes
	while (true) {
		Network::Address sender;
		unsigned char buffer[256];
		int bytesRead = _socket.receive(sender, buffer, sizeof(buffer));

		if (bytesRead <= 0 || sender.getAddress() != _address.getAddress()) {
			break;
		}

		Message msg;
		msg.init(buffer, bytesRead);

		//decipher header
		uint32_t ID = msg.readLong();
		uint32_t seq = msg.readLong();
		uint16_t connID = msg.readShort();
		uint8_t flags = msg.readByte();

		switch (_connection._state) {
		case Network::ConnState::CONNECTING:
			if (flags & (SYN | ACK)) {
				_connection = Network::Connection(_address, connID);
				_connection._state = Network::ConnState::CONNECTED;
				_gameState = GameState::PLAY;

				printf("client connected\n");

				//send ack
				_socket.sendAck(_connection._remoteAddress, 69420, _connection._id);
			}
			break;
		case Network::ConnState::CONNECTED:
			Network::Header header;
			uint16_t x1 = ((uint16_t *)(buffer + sizeof(header)))[0];
			uint16_t y1 = ((uint16_t *)(buffer + sizeof(header)))[1];
			uint16_t x2 = ((uint16_t *)(buffer + sizeof(header)))[2];
			uint16_t y2 = ((uint16_t *)(buffer + sizeof(header)))[3];
			//printf("1: %d, %d; 2: %d, %d\n", x1, y1, x2, y2);
		}
		
	}
	
	
	std::vector<MattEngine::Sprite *>::iterator i;
	for (i = _sprites.begin(); i != _sprites.end(); ++i) {
		(**i).update();
	}

	/*std::vector<Entity *>::iterator in;
	for (in = _bullets.begin(); in != _bullets.end(); ++in) {
		(**in).update();
	}*/
	for (int i = 0; i < _bullets.size(); i++) {
		_bullets[i]->update();
	}

	
}

void Game::render() {
	_window.clear();

	_colorProgram.use();

	//TEMP
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	GLint projecLocation = _colorProgram.getUniformLocation("projection");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(projecLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	glm::vec4 position(0, 0, 100, 100);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	float depth = 1.0f;
	static GLuint tex = MattEngine::ResourceManager::getTexture("res/xd.png");
	MattEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(position, uv, tex, depth, color);

	for (int i = 0; i < _bullets.size(); i++) {
		_bullets[i]->draw(_spriteBatch);
	}
	/*std::vector<Entity *>::iterator in;
	for (in = _bullets.begin(); in != _bullets.end(); ++in) {
		(**in).update();
	}*/

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_colorProgram.unuse();

	glfwSwapBuffers(_window.getWindow());
}
