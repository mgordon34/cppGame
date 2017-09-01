#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace MattEngine {

	class InputManager
	{
	public:
		static InputManager *getInstance();

		void update();

		void pressKey(int key);
		void releaseKey(int key);

		void setMouseCoords(float x, float y);

		bool isKeyPressed(int key);
		bool isKeyDown(int key);
		bool wasKeyDown(int key);
		glm::vec2 getMouseCoords();

	private:
		static InputManager* _instance;

		InputManager();
		//~InputManager();
		std::unordered_map<int, bool> _keyMap;
		std::unordered_map<int, bool> _oldMap;
		glm::vec2 _mouseCoords;


	};

}
