#pragma once

#include<GL/glew.h>
#include<map>

namespace MattEngine {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLuint getTexture(const char *filepath);
	private:
		std::map<const char *, GLuint> _textureMap;
	};

}