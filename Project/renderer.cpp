#include "globals.h"
#include "renderer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "material.h"

Renderer::~Renderer()
{
	delete _vertexBuffer;
	delete _indexBuffer;
	delete _vertexArray;
}

void Renderer::init() {
	// vertex data - raw data defining each of the vertices (which can contain position, normal, uv, etc)
	float w = 1.0f; // I want the texture's pixel size to be == to its size in the window
	float h = 1.0f;
	const int NUM_VERT = 4;
	const int ELEMENTS_PER_VERTEX = 4;

	// TODO make this 1 by 1 so that the model matrix can scale
	// move to a sprite renderer / sprite manager
	// apply a matrix to get the UVs

	float vertices[NUM_VERT * ELEMENTS_PER_VERTEX] = {
		0,			0,			0.0f, 0.0f,
		w,			0,			1.0f, 0.0f,
		w,			h,			1.0f, 1.0f,
		0,			h,			0.0f, 1.0f,
	};
	_vertexBuffer = DBG_NEW VertexBuffer(vertices, NUM_VERT * ELEMENTS_PER_VERTEX * sizeof(float)); // vertex buffer - allocates space for our vertex data on the GPU

	// index data - which vertices to use when drawing each tri
	const int NUM_IND = 6;
	unsigned int indices[NUM_IND] = {
		0, 1, 2,
		2, 3, 0,
	};
	_indexBuffer = DBG_NEW IndexBuffer(indices, NUM_IND); // vertex buffer - allocates space for our index data on the GPU

	// describes the actual layout of our vertces, so the gpu knows how to interperet
	VertexBufferLayout layout;
	layout.push<float>(2); // position coord
	layout.push<float>(2); // uv coord
	_vertexArray = DBG_NEW VertexArray(); // TODO still don't understand the vertex array???
	_vertexArray->AddBuffer(*_vertexBuffer, layout);
}

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

void Renderer::draw(Material* material, Vector2 position)
{
	_vertexArray->bind();
	_indexBuffer->bind();

	material->applyProperties();

	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	material->getShader()->setUniformMat4f("u_MVP", projectionMatrix);
	
	// How do I turn a pos (vec2) into a matrix?
	glm::mat4 modelViewMatrix = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	material->getShader()->setUniformMat4f("u_MVM", modelViewMatrix);

	GLCall(glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, NULL));
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
