#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace MattEngine {

	class SpriteSheet {

	public:
		SpriteSheet(const char *filepath);
		~SpriteSheet();

		void loadSS(const char *filepath);
		GLuint getTexID();

	private:
		const char *_filepath;
		GLuint _textureID;
	};

}