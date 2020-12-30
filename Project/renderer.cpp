#include "globals.h"
#include "renderer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"
#include <iostream>

void Renderer::glClearError() {
	while (glGetError() != GL_NO_ERROR) {}
}
bool Renderer::glCheckError(const char* function, const char* file, int line) {
	GLenum error = glGetError();
	while (error != GL_NO_ERROR) {
		printf("OpenGL Error %x\n\tLine %d\n\t%s\n\t%s\n", error, line, function, file);
		return false;
	}
	return true;
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.bind();
	va.bind();
	ib.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL)); // describes HOW we interperet the buffer data (we're reading vertices as triangles)
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
