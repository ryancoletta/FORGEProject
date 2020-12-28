#version 330 core

// runs on each vertex
// where would you like each vertex to be in the window

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

out vec3 out_color;

void main()
{
	gl_Position = vec4(in_position, 1.0);
	out_color = in_color;
}