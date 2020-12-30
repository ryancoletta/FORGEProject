#version 330 core

// runs on each pixel
// what color do you want this pixel to be

layout(location = 0) out vec4 frag_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec2 u_Direction;
uniform float u_Speed;
uniform float u_Time;

void main()
{
	vec2 movement = vec2(u_Direction.x + u_Time, u_Direction.y + u_Time) * u_Speed;
	vec2 uv = vec2(v_TexCoord.x + movement.x, v_TexCoord.y + movement.y) * 4.0;
	vec4 texColor = texture(u_Texture, uv);
	frag_Color = texColor;
}