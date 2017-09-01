#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "vertex.h"
#include "vector2.h"

namespace MattEngine {

	class Window;

	class Sprite {

	public:
		Sprite(Window *window);
		~Sprite();

		virtual void init(Vector2 position, float width, float height, const char *filepath);
		GLuint loadbmp(const char *filepath);
		GLuint loadpng(const char *filepath);

		Vector2 getPosition();
		void setPosition(Vector2 newVector);
		Vector2 getVelocity();
		void setVelocity(Vector2 newVector);

		virtual void update();
		void draw();

	protected:
		Window *_window;

		float _width;
		float _height;
		Vector2 _position;
		Vector2 _velocity;

	private:

		GLuint _vboID;
		GLuint _textureID;
	};

}