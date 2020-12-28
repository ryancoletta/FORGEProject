#pragma once
#include "globals.h"
#include <vector>
#include <GL/glew.h>
#include <iterator>;

class Drawable
{
public:
	Drawable();
	~Drawable();
	bool Draw();
protected:
	void loadVertices(float data[], size_t);
	void loadVertices(std::vector<float> data);

	void loadElements(GLuint data[], size_t size);
	void loadElements(std::vector<GLuint> data);

	void bindVAO();
	void unbindVAO();
private:
	GLuint _vao, _vbo, _ebo;
	std::vector<GLuint> _elements; // vars to update IN the shader
	std::vector<float> _vertices; // verts
};

