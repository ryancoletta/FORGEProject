#version 330 core

// runs on each pixel
// what color do you want this pixel to be

layout(location = 0) out vec4 frag_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform float u_Time;

void main()
{
	vec2 uv = v_TexCoord;
	frag_Color = texture(u_Texture, uv);
}