#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLuint buffer;
	glGenBuffers(1, &_rendererId);																	// generates the id of the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _rendererId);														// what to do with the buffer (make it an array of data)
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);										// fill the buffer with our data
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_rendererId);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
