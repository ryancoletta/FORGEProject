#version 330 core

// runs on each pixel
// what color do you want this pixel to be

layout(location = 0) out vec4 frag_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

uniform float u_Time;
uniform vec2 u_MovementDirection = vec2(0.0f, 1.0f);
uniform float u_MovementSpeed = 0.01f;
uniform int u_OscillationVariant = 3;
uniform float u_OscillationSpeed = 0.09f;
uniform float u_OscillationAmplitude = 10.0f;
uniform float u_OscillationDelay = 150.0f;

vec2 calcUV(vec2 uv, float scrollDirX, float scrollDirY, float scrollSpeed, int oscillationVariant, float oscillationSpeed, float oscillationAmplitude, float oscillationDelay)
{
	// background scrolling
	vec2 scrollDir = vec2(scrollDirX, scrollDirY) * u_Time * scrollSpeed;			//_Time is a float4 with different speeds in xyzw
	uv = uv + scrollDir;

	int pixelHeight = 256;															// float so that the amp is not set to 0
	int scanline = int(uv.y * pixelHeight);											// top = 0, bottom = 256
	float amp = oscillationAmplitude / pixelHeight;
	float pixelDelay = scanline * (oscillationDelay / pixelHeight);

	// choose which oscillation you'd like to display
	// note: switch statments are bad for performance in shaders, but this allows the most flexibility
	switch (oscillationVariant) {
	case 1:
		// horizontal oscillation
		uv.x = uv.x + sin((u_Time + pixelDelay) * oscillationSpeed) * amp;
		break;
	case 2:
		// interleaved oscillation
		int sign = (scanline % 2) * 2 - 1;											// returns either -1 or 1, saves an if statement with some math
		uv.x = uv.x + sign * sin((u_Time + pixelDelay) * oscillationSpeed) * amp;
		break;
	case 3:
		// vertical oscillation
		uv.y = uv.y + sin((u_Time + pixelDelay) * oscillationSpeed) * amp;
		break;
	}
	return uv;
}

void main()
{
	vec2 uv = v_TexCoord; 
	uv = calcUV(v_TexCoord, u_MovementDirection.x, u_MovementDirection.y, u_MovementSpeed, u_OscillationVariant, u_OscillationSpeed, u_OscillationAmplitude, u_OscillationDelay);
	frag_Color = texture(u_Texture, uv);
}