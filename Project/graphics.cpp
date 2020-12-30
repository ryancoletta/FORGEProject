#include "globals.h"
#include "graphics.h"
#include "shader.h"
#include <SDL_opengl.h>
#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "texture.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &_window, &_renderer);
	//SDL_SetRenderDrawColor(_renderer, 0xFF, 0x69, 0xB4, 0xFF); // debug pink
	SDL_SetWindowTitle(_window, "FORGE Project");

	initGL();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	delete _shader;
	delete _vertexBuffer;
	delete _indexBuffer;
	delete _vertexArray;
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// transparency - don't need, even with transparent pngs??
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendEquation(GL_FUNC_SUBTRACT);

	// what version of open GL is being used
	printf("%s\n", glGetString(GL_VERSION));

	// vertex data - raw data defining each of the vertices (which can contain position, normal, uv, etc)
	float size = 1.0f;
	const int NUM_VERT = 4;
	float positions[NUM_VERT * 4] = {
		-size, -size, 0.0f, 0.0f,
		 size, -size, 1.0f, 0.0f,
		 size,  size, 1.0f, 1.0f,
		-size,  size, 0.0f, 1.0f,
	};
	// index data - which vertices to use when drawing each tri
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	_vertexBuffer = DBG_NEW VertexBuffer(positions, NUM_VERT * 4 * sizeof(float)); // vertex buffer - allocates space for our vertex data on the GPU

	// describes the actual layout of our vertces, so the gpu knows how to interperet
	VertexBufferLayout layout;
	layout.push<float>(2); // organized as TWO floats, for position
	layout.push<float>(2); // uvs
	_vertexArray = DBG_NEW VertexArray(); // TODO still don't understand the vertex array???
	_vertexArray->AddBuffer(*_vertexBuffer, layout);

	_indexBuffer = DBG_NEW IndexBuffer(indices, 6); // vertex buffer - allocates space for our index data on the GPU

	// program to be run on the GPU to interperet the above data
	// vertex shader - how vertex positions are placed in the window
	// fragment shader - the color of each pixel in the window
	_shader = DBG_NEW Shader("test.vert", "test.frag");
	_shader->bind();

	Texture* texture = DBG_NEW Texture("Assets/pika.png");
	int textureSlot = 0;
	texture->bind(textureSlot);
	_shader->setUniform1i("u_Texture", textureSlot);
	_shader->setUniform2f("u_Direction", 1.0f, 1.0f);
	_shader->setUniform1f("u_Speed", 0.1f);

	// TODO unbind everything now, why???
	_shader->unbind();
	_vertexArray->unbind();
	_indexBuffer->unbind();
	_vertexBuffer->unbind();

	_rendererer = DBG_NEW Renderer();

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

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destRect, const int clockwiseRotationAngle) {
	SDL_RenderCopyEx(_renderer, texture, sourceRect, destRect, clockwiseRotationAngle, NULL, SDL_FLIP_NONE);
}

void Graphics::render() {
	_rendererer->clear();

	_shader->bind();
	_shader->setUniform1f("u_Time", SDL_GetTicks() * 0.001f);

	_rendererer->draw(*_vertexArray, *_indexBuffer, *_shader);

	SDL_GL_SwapWindow(_window);

	//SDL_RenderPresent(_renderer);
}

void Graphics::clear() { SDL_RenderClear(_renderer); }