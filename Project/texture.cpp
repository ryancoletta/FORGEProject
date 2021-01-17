#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path) : 
	_filePath(path),
	_localBuffer(NULL),
	_width(0),
	_height(0),
	_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	_localBuffer = stbi_load(path.c_str(), &_width, &_height, &_bpp, 4);

	glGenTextures(1, &_rendererId);
	bind(0); // TODO, if I don't bind here, it binds to slot zero implicitly somewhere else???

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//if rendered on a smaller area
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//if rendered on a larger area

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);		// horizontal wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);		// vertical wrap

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
	//unbind(); // TODO unbind so this starts in a clean state

	if (_localBuffer) {
		stbi_image_free(_localBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &_rendererId);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot); // 31 tex slots availible (tho not for all platforms)
	glBindTexture(GL_TEXTURE_2D, _rendererId);
}

/*
void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
*/
