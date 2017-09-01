#pragma once
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLSLProgram.h"
#include "vector2.h"
//#include "../entities/player.h"
#include "spritesheet.h"

namespace MattEngine {

	class Window {
	private:
		int _width, _height;
		const char *_name;
		GLFWwindow *_window;
		GLSLProgram _colorProgram;

		float _time;

	public:
		//CollisionBox _boundingBox;
	private:

	public:
		Window();
		~Window();

		int init(const char *name, int width, int height);
		bool closed() const;
		void clear() const;

		inline GLFWwindow* getWindow() { return _window; }
		inline int getWidth() { return _width; }
		inline int getHeight() { return _height; }
	};
}