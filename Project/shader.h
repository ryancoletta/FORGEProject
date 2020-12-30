#pragma once
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>

class Shader
{
public:
	Shader(std::string vertexFileName, std::string fragmentFileName);
	~Shader();
	void bind() const;
	void unbind() const;
	void setUniform1i(const std::string& name, GLint value);
	void setUniform1f(const std::string& name, GLfloat value);
	void setUniform2f(const std::string& name, GLfloat x, GLfloat y);
	void setUniform4f(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

private:
	std::string _vertSource, _fragSource;
	GLuint _vertexShader, _fragmentShader, _shaderProgram;
	std::unordered_map<std::string, int> _uniformLocationCache;

	bool load(std::string vertFileName, std::string fragFileName);
	bool compile();
	bool link();

	int getUniformLocation(const std::string& name);
};

