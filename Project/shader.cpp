#include "shader.h"
#include <Windows.h>

Shader::Shader(std::string vertexFileName, std::string fragmentFileName) :
	_vertFileName(vertexFileName),
	_fragFileName(fragmentFileName)
{
	_ready = false;
	if (!Load()) {
		printf("Error loading shader");
		return;
	}
	if (!Compile()) {
		printf("Error compiling shader");
		return;
	}
	if (!Link()) {
		printf("Error linking shader");
		return;
	}
	_ready = true;
}

Shader::~Shader() {

}

GLint Shader::getAttribute(std::string attributeName) {
	return glGetAttribLocation(_shaderProgram, attributeName.c_str());
}

bool Shader::Use() {
	if (_ready) {
		glUseProgram(_shaderProgram);
	}
	return _ready;
}

bool Shader::Load() {
	_vertFile.open(_vertFileName, std::ios::in);
	if (!_vertFile) {
		return false;
	}
	_vertSourceStream << _vertFile.rdbuf();

	_fragFile.open(_fragFileName, std::ios::in);
	if (!_fragFile) {
		return false;
	}
	_fragSourceStream << _fragFile.rdbuf();

	_vertSource = _vertSourceStream.str();
	_fragSource = _fragSourceStream.str();

	return true;
}

bool Shader::Compile() {

	const char* tempSource = _vertSource.c_str();
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(_vertexShader, 1, &tempSource, NULL);
	glCompileShader(_vertexShader);

	GLint compiled = GL_FALSE;
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &compiled); // get status of compilation
	if (!compiled) {
		// print the error log
		unsigned int maxLength;
		glGetShaderiv(_vertexShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* vertexCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(_vertexShader, maxLength, (GLint*)&maxLength, vertexCompileLog);
		printf("ERROR:%s", vertexCompileLog);
		free(vertexCompileLog);
		return false;
	}

	tempSource = _fragSource.c_str();
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShader, 1, &tempSource, 0);
	glCompileShader(_fragmentShader);

	compiled = GL_FALSE;
	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &compiled); // get status of compilation
	if (!compiled) {
		// print the error log
		unsigned int maxLength;
		glGetShaderiv(_fragmentShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* fragmentCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(_fragmentShader, maxLength, (GLint*)&maxLength, fragmentCompileLog);
		printf("ERROR:%s", fragmentCompileLog);
		free(fragmentCompileLog);
		return false;
	}
	
	return true;
}

bool Shader::Link() {
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);
	glValidateProgram(_shaderProgram);
	
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);

	GLint linked = GL_FALSE;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linked);
	if (!linked) {
		// print the error log
		unsigned int maxLength;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* programLinkLog = (char*)malloc(maxLength);
		glGetProgramInfoLog(_shaderProgram, maxLength, (GLint*)&maxLength, programLinkLog);
		printf("ERROR:%s", programLinkLog);
		free(programLinkLog);
		return false;
	}

	return true;
}