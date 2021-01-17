#pragma once
#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot) const;
	//void unbind() const;

	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }
private:
	GLuint _rendererId;
	std::string _filePath;
	unsigned char* _localBuffer;
	int _width, _height, _bpp;
};

