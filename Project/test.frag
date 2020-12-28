#version 330 core

// runs on each pixel
// what color do you want this pixel to be

in vec3 in_color;

out vec4 frag_color;

void main()
{
	frag_color = vec4(1.0, 0.0, 1.0, 1.0);
}