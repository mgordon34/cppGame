#include "window.h"
#include "vector2.h"

namespace MattEngine {

	void windowResize(GLFWwindow* window, int width, int height);

	Window::Window() {

	}

	int Window::init(const char *name, int width, int height) {
		_name = name;
		_width = width;
		_height = height;
		_time = 0.0f;

		glfwInit();
		_window = glfwCreateWindow(_width, _height, _name, NULL, NULL);
		if (!_window) {
			std::cout << "Error" << std::endl;
			glfwTerminate();
			return 1;
		}

		glfwMakeContextCurrent(_window);
		glfwSetWindowSizeCallback(_window, windowResize);
		glfwSwapInterval(0);

		if (glewInit() != GLEW_OK) {
			std::cout << "Could not initialize GLEW" << std::endl;
			return 1;
		}

		std::cout << "OPENGL: " << glGetString(GL_VERSION) << std::endl;

		glViewport(0.0f, 0.0f, _width, _height);

		glEnable(GL_TEXTURE_2D);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, _width, 0.0f, _height, 0.0f, 100);
		glMatrixMode(GL_MODELVIEW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//_boundingBox = makeCollBox(_height, 0, 0, _width);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		return 0;
	}

	Window::~Window() {
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(_window);
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void windowResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

}