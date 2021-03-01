#pragma once
#include "renderer.h"

class IndexBuffer
{
public:
	IndexBuffer(const GLuint* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int GetCount() const { return _count; }

private:
	GLuint _rendererId;
	unsigned int _count;
};

