#pragma once
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) Renderer::glClearError();\
	x;\
	ASSERT(Renderer::glCheckError(#x, __FILE__, __LINE__))

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void clear() const;
private:
	void glClearError();
	bool glCheckError(const char* function, const char* file, int line);
};