#version 330 core

// runs on each vertex
// where would you like each vertex to be in the window

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec2 in_TexCoord;
layout(location = 2) in float in_TexIdx;

out vec2 v_TexCoord;
out float v_TexIdx;

// projection matrix, i.e. camera
uniform mat4 u_MVP;

// model view matrix, sprite transform
uniform mat4 u_MVM;

// UV matrix, draw sprite within sheet
uniform mat4 u_UVM;

void main()
{
	// where do I put u_MVM and u_UVM???
	gl_Position = u_MVP * in_Position;
	v_TexCoord = in_TexCoord;
	v_TexIdx = in_TexIdx;
}