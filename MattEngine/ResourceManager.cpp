#include "ResourceManager.h"

namespace MattEngine {

	TextureCache ResourceManager::_textureCache;

	GLuint ResourceManager::getTexture(const char *filepath) {
		return _textureCache.getTexture(filepath);
	}

}