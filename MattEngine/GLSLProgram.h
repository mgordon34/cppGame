#pragma once

#include <GL\glew.h>
#include <string>

namespace MattEngine {

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(std::string vertShaderFilepath, std::string fragShaderFilepath);

		void linkShaders();

		void addAttribute(std::string attribName);

		GLint getUniformLocation(std::string uniformName);

		void use();
		void unuse();

	private:
		GLuint _programID;
		GLuint _vertShaderID;
		GLuint _fragShaderID;

		int _numAttributes;

		void compileShader(std::string filepath, GLuint id);
	};

}