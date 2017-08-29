#pragma once

#include "TextureCache.h"

namespace MattEngine {

	class ResourceManager
	{
	public:
		static GLuint getTexture(const char *filepath);

	private:
		static TextureCache _textureCache;
	};

}