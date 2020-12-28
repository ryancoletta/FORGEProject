#include "drawable.h"

Drawable::Drawable() {
	_vao = 0;
	_vbo = 0; 
	_ebo = 0;

	glGenVertexArrays(1, &_vao);

}

void Drawable::bindVAO() {
	glBindVertexArray(_vao);
}

void Drawable::unbindVAO() {
	glBindVertexArray(_vao);
}