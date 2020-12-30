#version 330 core

// runs on each vertex
// where would you like each vertex to be in the window

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(in_Position, 1.0);
	v_TexCoord = in_TexCoord;
}