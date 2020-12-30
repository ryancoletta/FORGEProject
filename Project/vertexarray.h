#pragma once
#include <GL/glew.h>
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
private:
	GLuint _rendererId;
};

