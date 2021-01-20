#version 330 core

// runs on each vertex
// where would you like each vertex to be within the window

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec2 in_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform vec2 u_UVOffset;
uniform vec2 u_UVScale;

void main()
{
	gl_Position = u_MVP * in_Position;
	v_TexCoord = in_TexCoord * u_UVScale + u_UVOffset;
}