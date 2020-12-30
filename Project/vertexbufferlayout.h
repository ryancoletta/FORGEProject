#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexBufferElement {
	GLuint type;
	unsigned int count;
	unsigned int normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) 
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_BYTE:			return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : _stride(0) {}

	template<typename T> 
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<> 
	void push<float>(unsigned int count) {
		_elements.push_back({GL_FLOAT, count, GL_FALSE});
		_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count) {
		_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void push<unsigned char>(unsigned int count) {
		_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline unsigned int GetStride() const { return _stride; }
	inline const std::vector<VertexBufferElement> GetElements() const& { return _elements; }

private:
	std::vector<VertexBufferElement> _elements;
	unsigned int _stride;
};

