#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

namespace MattEngine {

	typedef struct myVector2 {
		GLfloat x;
		GLfloat y;
	} Vector2;

	Vector2 makeVector2(GLfloat x, GLfloat y);
	Vector2 addVector2(Vector2 first, Vector2 second);

}