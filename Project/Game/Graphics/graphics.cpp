#include "globals.h"
#include "graphics.h"
#include "shader.h"
#include <SDL_opengl.h>
#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "texture.h"

Graphics* Graphics::instance = nullptr;

Graphics::Graphics()
{
	_window = SDL_CreateWindow("FORGE Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	initGL();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	delete _renderer;

	std::map<std::string, Texture*>::iterator it1;
	for (it1 = _textures.begin(); it1 != _textures.end(); it1++)
	{
		delete it1->second;
	}
	_textures.clear();

	std::map<std::string, Shader*>::iterator it2;
	for (it2 = _shaders.begin(); it2 != _shaders.end(); it2++)
	{
		delete it2->second;
	}
	_shaders.clear();
}

bool Graphics::initGL() {
	// GLEW requires a valid openGL context before initialization
	if (SDL_GL_CreateContext(_window) == nullptr)
	{
		printf("OpenGL context could not be created");
		return false;
	}
	if (glewInit() != GLEW_OK)
	{
		printf("Error initializing GLEW");
		return false;
	}

	// set gl version, don't using anything beyond that
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	printf("%s\n", glGetString(GL_VERSION)); // TODO why is this not 3.3?

	// transparency - TODO doesn't work!
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	_renderer = DBG_NEW Renderer();
	_renderer->init();

	return true;
}


Texture* Graphics::loadTexture(const std::string& filePath) {
	if (_textures.count(filePath) == 0) {
		_textures[filePath] = DBG_NEW Texture(filePath);
	}
	return _textures[filePath];
}

Shader* Graphics::loadShader(const std::string& vertPath, const std::string& fragPath)
{
	std::string shaderName = vertPath + fragPath; // TODO kinda weird way to cache, having a name might be appropriate
	if (_shaders.count(shaderName) == 0) {
		_shaders[shaderName] = DBG_NEW Shader(vertPath, fragPath);
	}
	return _shaders[shaderName];
}


void Graphics::draw(Texture* texture, Texture* palette, Shader* shader, SDL_Rect sourceRect, SDL_Rect destRect, const float clockwiseRotationAngle)
{
	_renderer->draw(texture, palette, shader, sourceRect, destRect, clockwiseRotationAngle);
}

void Graphics::begin()
{
	// TODO set global shader constants
}

void Graphics::render() { SDL_GL_SwapWindow(_window); }

void Graphics::clear() { _renderer->clear(); }


