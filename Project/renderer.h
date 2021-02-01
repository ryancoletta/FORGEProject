#pragma once
#include "globals.h"
#include <GL/glew.h>
#include <SDL_rect.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) Renderer::glClearError();\
	x;\
	ASSERT(Renderer::glCheckError(#x, __FILE__, __LINE__))

class IndexBuffer;
class VertexBuffer;
class VertexArray;
class Texture;
class Shader;

class Renderer {
public:
	~Renderer();
	void init();
	void draw(Texture* texture, Texture* palette, Shader* shader, SDL_Rect sourceRect, SDL_Rect destinationRect, const float clockwiseRotationAngle);
	void clear() const;

	// stores all of the things I wish to draw and draws them
	// submit(va, material, transform)
	// vedrtex AND index buffers are all the same for a 2d game (quads)
	// sprite needs a UV transform and a positionary Transform

private:

	IndexBuffer* _indexBuffer;		// allocates space for data on the GPU regarding which verticies to use when drawing tris
	VertexBuffer* _vertexBuffer;	// allocates space for data on the GPU regarding verticies
	VertexArray* _vertexArray;		// describes the layout of the data bound in the vertex buffer, so the GPU knows how to interperet it

	void glClearError();
	bool glCheckError(const char* function, const char* file, int line);
};