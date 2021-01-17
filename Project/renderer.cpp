#include "globals.h"
#include "renderer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "material.h"
#include "texture.h"

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

void Renderer::draw(Material* material, SDL_Rect sourceRect, SDL_Rect destinationRect) // TODO pass sourceRect
{
	_vertexArray->bind();
	_indexBuffer->bind();

	material->applyProperties();

	// sprite transform 
	glm::vec3 uvSpacePosition = glm::vec3((float)destinationRect.x / globals::WINDOW_WIDTH, (float)destinationRect.y / globals::WINDOW_HEIGHT, 0.0f);
	glm::vec3 uvSpaceScale = glm::vec3((float)destinationRect.w / globals::WINDOW_WIDTH, (float)destinationRect.h / globals::WINDOW_HEIGHT, 0.0f);

	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 modelPositionMatrix = glm::translate(glm::mat4(1.0f), uvSpacePosition);
	glm::mat4 modelScaleMatrix = glm::scale(glm::mat4(1.0f), uvSpaceScale);
	glm::mat4 mvp = projectionMatrix * modelPositionMatrix * modelScaleMatrix;

	material->getShader()->setUniformMat4f("u_MVP", mvp);

	// find which sprite to use within the sprite sheet
	float w = material->getTexture()->getWidth();
	float h = material->getTexture()->getHeight();

	// accounts for the fact that GL coords start from the bottom left and SDL coords start from the top left
	glm::vec2 uvOffset = glm::vec2((float)(sourceRect.x / w), (float)((h - sourceRect.y - sourceRect.h) / h)); // TODO WRONG
	glm::vec2 uvScale = glm::vec2((float)sourceRect.w / w, (float)sourceRect.h / h); // RIGHT!
	material->getShader()->setUniform2f("u_UVOffset", uvOffset.x, uvOffset.y);
	material->getShader()->setUniform2f("u_UVScale", uvScale.x, uvScale.y);


	material->getShader()->setUniform1f("u_Time", SDL_GetTicks() * 0.01f);

	GLCall(glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, NULL));
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
