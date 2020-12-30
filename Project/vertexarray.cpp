#include "vertexarray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_rendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_rendererId);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {

		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset); // links buffer to vao
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(_rendererId);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
