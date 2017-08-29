#include "GLSLProgram.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace MattEngine {

	GLSLProgram::GLSLProgram() : _programID(0), _vertShaderID(0), _fragShaderID(0), _numAttributes(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(std::string vertShaderFilepath, std::string fragShaderFilepath) {
		_programID = glCreateProgram();

		_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertShaderID == 0) {
			std::cout << "shits wrong with vertshader" << std::endl;
		}
		_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragShaderID == 0) {
			std::cout << "shits wrong with fragshader" << std::endl;
		}

		compileShader(vertShaderFilepath, _vertShaderID);
		compileShader(fragShaderFilepath, _fragShaderID);

	}

	void GLSLProgram::compileShader(std::string filepath, GLuint id) {
		std::ifstream shaderFile(filepath);
		if (shaderFile.fail()) {
			std::cout << "failed to open vertshaderfilepath" << std::endl;
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(shaderFile, line)) {
			fileContents += line + "\n";

		}

		shaderFile.close();

		const char *contentsptr = fileContents.c_str();
		glShaderSource(id, 1, &contentsptr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.
			std::printf("%s\n", &errorLog[0]);
			std::cout << filepath << std::endl;
			return;
		}
	}

	void GLSLProgram::linkShaders() {
		//Vertex and fragment shaders are successfully compiled.
		//Now time to link them together into a program.
		//Get a program object.

		//Attach our shaders to our program
		glAttachShader(_programID, _vertShaderID);
		glAttachShader(_programID, _fragShaderID);

		//Link our program
		glLinkProgram(_programID);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertShaderID);
			glDeleteShader(_fragShaderID);

			//Use the infoLog as you see fit.

			//In this simple program, we'll just leave
			return;
		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertShaderID);
		glDetachShader(_programID, _fragShaderID);
		glDeleteShader(_vertShaderID);
		glDeleteShader(_fragShaderID);
	}

	void GLSLProgram::addAttribute(std::string attribName) {
		glBindAttribLocation(_programID, _numAttributes++, attribName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(std::string uniformName) {
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			//std::cout << "not found in shader bitch" << std::endl;
		}

		return location;
	}


	void GLSLProgram::use() {
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}
}

