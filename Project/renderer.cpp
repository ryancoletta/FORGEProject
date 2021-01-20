#include "globals.h"
#include "renderer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"

Renderer::~Renderer()
{
	delete _vertexBuffer;
	delete _indexBuffer;
	delete _vertexArray;
}

void Renderer::init() {
	// vertex data - raw data defining each of the vertices (which can contain xy, uv)
	float w = 0.5f;
	float h = 0.5f;
	const int NUM_VERT = 4;
	const int ELEMENTS_PER_VERTEX = 4;

	float vertices[NUM_VERT * ELEMENTS_PER_VERTEX] = {
		-0.5f,	-0.5f,	0.0f, 0.0f,
		w,		-0.5f,	1.0f, 0.0f,
		w,		h,		1.0f, 1.0f,
		-0.5f,	h,		0.0f, 1.0f,
	};

	// vertex buffer - allocates space for our vertex data on the GPU
	_vertexBuffer = DBG_NEW VertexBuffer(vertices, NUM_VERT * ELEMENTS_PER_VERTEX * sizeof(float)); 

	// index data - which vertices to use when drawing each tri
	const int NUM_IND = 6;
	unsigned int indices[NUM_IND] = {
		0, 1, 2,
		2, 3, 0,
	};
	// index buffer - allocates space for our index data on the GPU
	_indexBuffer = DBG_NEW IndexBuffer(indices, NUM_IND); 

	// vertex array - describes the actual layout of our vertces, so the gpu knows how to interperet
	VertexBufferLayout layout;
	layout.push<float>(2); // xy coord
	layout.push<float>(2); // uv coord
	_vertexArray = DBG_NEW VertexArray();
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

void Renderer::draw(Texture* texture, Shader* shader, SDL_Rect sourceRect, SDL_Rect destinationRect, const float clockwiseRotationAngle)
{
	_vertexArray->bind();
	_indexBuffer->bind();

	// sprite transform - move, scale, rotate the sprite within the window
	glm::vec3 screenSpacePosition = glm::vec3((float)destinationRect.x, (float)destinationRect.y, 0.0f);
	glm::vec3 screenSpaceScale = glm::vec3((float)destinationRect.w, (float)destinationRect.h, 0.0f);

	glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)globals::WINDOW_WIDTH, (float)globals::WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f); // TODO up is now down, fix
	glm::mat4 modelPositionMatrix = glm::translate(glm::mat4(1.0f), screenSpacePosition);
	glm::mat4 modelScaleMatrix = glm::scale(glm::mat4(1.0f), screenSpaceScale);
	glm::mat4 modelRotationMatrix = glm::rotate(glm::mat4(1.0f), (float)glm::radians(clockwiseRotationAngle), glm::vec3(0, 0, 1));
	glm::mat4 ctm = modelPositionMatrix * modelScaleMatrix * modelRotationMatrix;
	glm::mat4 mvp = projectionMatrix * ctm;  

	shader->setUniformMat4f("u_MVP", mvp);

	// sprite sheet lookup - modify the UV to capture the correct sprite
	float w = texture->getWidth();
	float h = texture->getHeight();

	// accounts for the fact that GL coords start from the bottom left and SDL coords start from the top left
	glm::vec2 uvOffset = glm::vec2((float)(sourceRect.x / w), (float)((h - sourceRect.y - sourceRect.h) / h));
	glm::vec2 uvScale = glm::vec2((float)sourceRect.w / w, (float)sourceRect.h / h);
	shader->setUniform2f("u_UVOffset", uvOffset.x, uvOffset.y);
	shader->setUniform2f("u_UVScale", uvScale.x, uvScale.y);

	GLCall(glDrawElements(GL_TRIANGLES, _indexBuffer->GetCount(), GL_UNSIGNED_INT, NULL));
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
