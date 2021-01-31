#include "shader.h"
#include <Windows.h>

Shader::Shader(std::string vertexFileName, std::string fragmentFileName)
{
	// TODO just initialize, do these elsewhere or else you'll get a broken class

	if (!load(vertexFileName, fragmentFileName)) {
		printf("Error loading shader");
		return;
	}
	if (!compile()) {
		printf("Error compiling shader");
		return;
	}
	if (!link()) {
		printf("Error linking shader");
		return;
	}
}

Shader::~Shader() {
	glDeleteProgram(_shaderProgram);
}

void Shader::bind() const {
	glUseProgram(_shaderProgram); // opaque pointer
}

void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::setUniform1iv(const std::string& name, const unsigned int& count, GLint* value)
{
	glUniform1iv(getUniformLocation(name), count, value);
}

void Shader::setUniform1i(const std::string& name, GLint value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, GLfloat value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform2f(const std::string& name, GLfloat x, GLfloat y)
{
	glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setUniform4f(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::getUniformLocation(const std::string& name)
{
	if (_uniformLocationCache.find(name) != _uniformLocationCache.end()) {
		return _uniformLocationCache[name];
	}

	int location = glGetUniformLocation(_shaderProgram, name.c_str());
	if (location == -1) {
		printf("Warning: uniform %s does not exist OR is unused\n", name.c_str());
	}
	_uniformLocationCache[name] = location;
	return location;
}

bool Shader::load(std::string vertFileName, std::string fragFileName) {
	std::ifstream _vertFile, _fragFile;
	
	std::stringstream _vertSourceStream, _fragSourceStream;
	_vertFile.open(vertFileName, std::ios::in);
	if (!_vertFile) {
		return false;
	}
	_vertSourceStream << _vertFile.rdbuf();

	_fragFile.open(fragFileName, std::ios::in);
	if (!_fragFile) {
		return false;
	}
	_fragSourceStream << _fragFile.rdbuf();

	_vertSource = _vertSourceStream.str();
	_fragSource = _fragSourceStream.str();

	return true;
}

bool Shader::compile() {

	const char* tempSource = _vertSource.c_str();
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(_vertexShader, 1, &tempSource, nullptr);
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

bool Shader::link() {
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