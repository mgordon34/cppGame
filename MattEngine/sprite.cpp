#include "sprite.h"
#include "vertex.h"
#include <SOIL/SOIL.h>
#include "window.h"

#include "ResourceManager.h"

namespace MattEngine {

	Sprite::Sprite(Window *window) {
		_window = window;
		_vboID = 0;
	}

	Sprite::~Sprite() {
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
		if (_textureID != 0) {
			glDeleteTextures(1, &_textureID);
		}
	}

	void Sprite::init(Vector2 position, float width, float height, const char *filepath) {
		_position = position;
		_velocity = makeVector2(0, 0);

		_width = width;
		_height = height;

		//_textureID = loadpng("res/xd2.png");
		_textureID = ResourceManager::getTexture(filepath);

		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[4];
		vertexData[0].setPosition(position.x, position.y + height);
		vertexData[0].setUV(0.5f, 1.0f);
		//vertexData[0].texturepos.x = 0.5f;
		//vertexData[0].texturepos.y = 0.0f;

		vertexData[1].setPosition(position.x, position.y);
		vertexData[1].setUV(0.5f, 0.0f);

		//vertexData[1].texturepos.x = 0.5f;
		//vertexData[1].texturepos.y = 1.0f;

		vertexData[2].setPosition(position.x + width, position.y);
		vertexData[2].setUV(1.0f, 0.0f);

		//vertexData[2].texturepos.x = 1.0f;
		//vertexData[2].texturepos.y = 1.0f;

		vertexData[3].setPosition(position.x + width, position.y + height);
		vertexData[3].setUV(1.0f, 1.0f);
		//vertexData[3].texturepos.x = 1.0f;
		//vertexData[3].texturepos.y = 0.0f;

		for (int i = 0; i < 4; i++) {
			vertexData[i].setColor(255, 0, 255, 255);
		}

		vertexData[0].setColor(0, 0, 255, 255);

		vertexData[2].setColor(0, 255, 0, 255);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//_textureID = loadpng(filepath);
		//_textureID = textureID;
		std::cout << _textureID << std::endl;
		//glBindBuffer(GL_TEXTURE_2D, textureID);

	}

	void Sprite::setVelocity(Vector2 newVector) {
		_velocity = newVector;
	}
	Vector2 Sprite::getVelocity() {
		return _velocity;
	}

	GLuint Sprite::loadbmp(const char *filepath) {
		unsigned char header[54];
		unsigned int dataPos;
		unsigned int width, height;
		unsigned int imageSize;

		unsigned char * data;

		FILE * file = fopen(filepath, "rb");
		if (!file) {
			std::cout << "file not loaded!" << std::endl;
			exit(0);
		}

		fread(header, sizeof(unsigned char), 54, file);

		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[18]);
		height = *(int*)&(header[22]);

		if (imageSize == 0) {
			imageSize = width * height * 3;
		}

		if (dataPos == 0) {
			dataPos = 54;
		}

		data = new unsigned char[imageSize];
		fread(data, 1, imageSize, file);
		fclose(file);

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		return textureID;
	}

	GLuint Sprite::loadpng(const char *filepath) {
		//GLuint textureID = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
		//(
		//	filepath,
		//	SOIL_LOAD_AUTO,
		//	SOIL_CREATE_NEW_ID,
		//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		//);
		int w = 100;
		int h = 100;
		unsigned char* image = SOIL_load_image(filepath, &w, &h, 0, SOIL_LOAD_RGBA);

		if (image == NULL) {
			std::cout << "shits wrong" << std::endl;
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
		return textureID;
	}

	void Sprite::update() {
		//_velocity = makeVector2(0, 0);
		//if (glfwGetKey(_window, GLFW_KEY_UP)) {
		//	_velocity = addVector2(_velocity, makeVector2(0.0f, 1.0f));
		//}
		//_position = addVector2(_position, _velocity);
	}

	void Sprite::draw() {
		glBindTexture(GL_TEXTURE_2D, _textureID);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Position Attribute Pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		//Color Attribute Pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		//UV Attribute Pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));


		//glLoadIdentity();
		//glTranslatef(_position.x, _position.y, 0);

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, _textureID);
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void *)offsetof(Vertex, texturepos));

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
}