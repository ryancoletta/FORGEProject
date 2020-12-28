#include "globals.h"
#include "graphics.h"
#include "globals.h"
#include "shader.h"
#include <SDL_opengl.h>

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(globals::WINDOW_WIDTH, globals::WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &_window, &_renderer);
	//SDL_SetRenderDrawColor(_renderer, 0xFF, 0x69, 0xB4, 0xFF); // debug pink
	SDL_SetWindowTitle(_window, "FORGE Project");

	if (initGL()) {
		// what version of open GL is being used
		printf("%s", glGetString(GL_VERSION));

		// vertex data
		const int NUM_VERT = 3;
		float positions[NUM_VERT * 2] = {
			-1.0f, -1.0f,
			 0.0f,  1.0f,
			 1.0f, -1.0f,
		};

		// buffer - memory we want our gpu to use
		GLuint buffer; 
		glGenBuffers(1, &buffer);																	// generates the id of the buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffer);														// what to do with the buffer (make it an array of data)
		glBufferData(GL_ARRAY_BUFFER, NUM_VERT * 2 * sizeof(float), positions, GL_DYNAMIC_DRAW);	// fill the buffer with data

		// we need to now organize our data so the GPU knows what you're describing w/ data (like a struct)
		// gl float is the data type
		// gl int describes how many floats per data object
		// stride describes the memory between data objects
		// pointer is a pointer to the first attribute within each data object
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		glEnableVertexAttribArray(0);

		_shader = DBG_NEW Shader("test.vert", "test.frag");
		_shader->Use();
	}
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	delete _shader;
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
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3); // describes HOW we interperet the buffer data (we're reading vertices)

	SDL_GL_SwapWindow(_window);

	//SDL_RenderPresent(_renderer);
}

void Graphics::clear() { SDL_RenderClear(_renderer); }