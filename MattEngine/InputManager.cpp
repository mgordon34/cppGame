#include "InputManager.h"

namespace MattEngine {

	InputManager *InputManager::_instance = NULL;


	InputManager* InputManager::getInstance() {
		if (!_instance) {
			_instance = new InputManager;
		}
		return _instance;
	}

	InputManager::InputManager()
	{
	}

	//InputManager::~InputManager()
	//{
	//}
	
	void InputManager::update() {
		for (auto it = _keyMap.begin(); it != _keyMap.end(); it++) {
			_oldMap[it->first] = it->second;
		}
	}

	void InputManager::pressKey(int key) {
		_keyMap[key] = true;
	}

	void InputManager::releaseKey(int key) {
		_keyMap[key] = false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyDown(int key) {
		auto it = _keyMap.find(key);
		if (it == _keyMap.end()) {
			return false;
		}
		return it->second;
	}

	bool InputManager::wasKeyDown(int key) {
		auto it = _oldMap.find(key);
		if (it == _oldMap.end()) {
			return false;
		}
		return it->second;
	}

	bool InputManager::isKeyPressed(int key) {
		if (isKeyDown(key) == true && wasKeyDown(key) == false) {
			return true;
		}
		return false;
	}

	glm::vec2 InputManager::getMouseCoords() {
		return _mouseCoords;
	}
}