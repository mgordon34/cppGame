#include "spritesheet.h"
#include <SOIL/SOIL.h>
#include <iostream>

namespace MattEngine {

	SpriteSheet::SpriteSheet(const char *filepath) {
		loadSS(filepath);
	}

	SpriteSheet::~SpriteSheet() {
		if (_textureID != 0) {
			glDeleteTextures(1, &_textureID);
		}
	}

	GLuint SpriteSheet::getTexID() {
		return _textureID;
	}

	void SpriteSheet::loadSS(const char *filepath) {
		_filepath = filepath;
		//_textureID = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
		//(
		//	filepath,
		//	SOIL_LOAD_AUTO,
		//	SOIL_CREATE_NEW_ID,
		//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		//);

		int w = 100;
		int h = 100;
		unsigned char* image = SOIL_load_image(filepath, &w, &h, 0, SOIL_LOAD_RGBA);

		if (!image) {
			std::cout << "shits wrongt" << std::endl;
		}

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		SOIL_free_image_data(image);

		_textureID = textureID;
	}
}