#pragma once
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


class Shader
{
public:
	Shader(std::string vertexFileName, std::string fragmentFileName);
	~Shader();
	GLint getAttribute(std::string attributeName);
	bool Use();
private:
	std::ifstream _vertFile, _fragFile;
	std::string _vertFileName, _fragFileName;
	std::stringstream _vertSourceStream, _fragSourceStream;
	std::string _vertSource, _fragSource;
	GLuint _vertexShader, _fragmentShader, _shaderProgram;
	bool _ready;

	bool Load();
	bool Compile();
	bool Link();
};

