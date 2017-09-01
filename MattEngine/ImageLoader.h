#pragma once

#include <GL/glew.h>

namespace MattEngine {

	class ImageLoader
	{
	public:
		static GLuint loadPicture(const char *filepath);
	};

}