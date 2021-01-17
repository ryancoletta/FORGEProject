#include "globals.h"
#include "graphics.h"
#include "shader.h"
#include <SDL_opengl.h>
#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "material.h"

Graphics::Graphics()
{
	//_window = SDL_CreateWindow("FORGE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_CreateWindowAndRenderer(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &_window, &_renderer);
	//SDL_SetRenderDrawColor(_renderer, 0xFF, 0x69, 0xB4, 0xFF); // debug pink
	SDL_SetWindowTitle(_window, "FORGE Project");

	initGL();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	delete _rendererer;
}

bool Graphics::initGL() {
	// GLEW requires a valid openGL context befor initialization
	if (SDL_GL_CreateContext(_window) == NULL)
	{
		printf("OpenGL context could not be created!");
		return false;
	}
	if (glewInit() != GLEW_OK)
	{
		printf("Error initializing GLEW!");
		return false;
	}

	// set gl version, don't using anything beyond that
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// transparency - TODO doesn't work!
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_SUBTRACT);

	// what version of open GL is being used
	printf("%s\n", glGetString(GL_VERSION)); // TODO why is this not 3.3?

	// program to be run on the GPU to interperet the above data
	// vertex shader - how vertex positions are placed in the window
	// fragment shader - the color of each pixel in the window

	_rendererer = DBG_NEW Renderer();
	_rendererer->init();

	return true;
}

SDL_Renderer* Graphics::getRenderer() const { return _renderer; }

SDL_Surface* Graphics::loadImage(const std::string& filePath) {
	if (_spriteSheets.count(filePath) == 0) {
		_spriteSheets[filePath] = IMG_Load(filePath.c_str());
		SDL_SetColorKey(_spriteSheets[filePath], SDL_TRUE, SDL_MapRGB(_spriteSheets[filePath]->format, 0, 0xFF, 0xFF));
	}
	return _spriteSheets[filePath];
}

Texture* Graphics::loadTexture(const std::string& filePath) {
	if (_textures.count(filePath) == 0) {
		_textures[filePath] = DBG_NEW Texture(filePath);
	}
	return _textures[filePath];
}

Shader* Graphics::loadShader(const std::string& vertPath, const std::string& fragPath)
{
	if (_shaders.count(vertPath) == 0) { // TODO cache should account for frag path as well
		_shaders[vertPath] = DBG_NEW Shader(vertPath, fragPath);
	}
	return _shaders[vertPath];
}

Material* Graphics::loadMaterial(const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale)
{
	Texture* texture = loadTexture(texturePath);
	Shader* shader = loadShader(vertPath, fragPath);
	return DBG_NEW Material(texture, shader, sourcePosition, sourceScale);
}

// TODO replace THIS
void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect, const int clockwiseRotationAngle) {
	SDL_RenderCopyEx(_renderer, texture, sourceRect, destRect, clockwiseRotationAngle, NULL, SDL_FLIP_NONE);
}

// TODO with THIS
void Graphics::draw(Material* material, SDL_Rect destRect, const float clockwiseRotationAngle)
{

	// pass in a material and a transform position
	_rendererer->draw(material, material->getSourceRect(), destRect, clockwiseRotationAngle);
}

void Graphics::render() {
	SDL_GL_SwapWindow(_window);
	
	//SDL_RenderPresent(_renderer);
}

void Graphics::clear() { 
	//SDL_RenderClear(_renderer); 
	_rendererer->clear();
}


