#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class Shader;
class IndexBuffer;
class VertexBuffer;
class VertexArray;
class Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	SDL_Renderer* getRenderer() const;

	SDL_Surface* loadImage(const std::string& filePath);
	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect, const int clockWiseAngleRotation = 0);
	void render();
	void clear();

	bool initGL();

private:
	Renderer* _rendererer;
	IndexBuffer* _indexBuffer;		// allocates space for data on the GPU regarding which verticies to use when drawing tris
	VertexBuffer* _vertexBuffer;	// allocates space for data on the GPU regarding verticies
	VertexArray* _vertexArray;		// describes the layout of the data bound in the vertex buffer, so the GPU knows how to interperet it
	Shader* _shader;				// program that runs on the gpu using the provided data to display each pixel

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Surface*> _spriteSheets;
};

