#version 330 core

// runs on each pixel
// what color do you want this pixel to be

layout(location = 0) out vec4 frag_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Palette;

uniform float u_Time;

vec4 paletteSwap(vec4 baseColor) 
{

	float increaseAmt = ceil((sin(u_Time * 0.2) / 4.0 + 0.25) * 100) / 100;
	//increaseAmt = 0;

	if (baseColor.r > 0.0) 
	{
		float colorIndex = 0.0;
		float shadeIndex = 0.5 - baseColor.r / 2;
		shadeIndex += increaseAmt;

		baseColor = texture(u_Palette, vec2(shadeIndex, colorIndex));
	}
	else if (baseColor.g > 0.0) 
	{
		float colorIndex = 0.34;
		float shadeIndex = 0.5 - baseColor.g / 2;
		shadeIndex += increaseAmt;

		baseColor = texture(u_Palette, vec2(shadeIndex, colorIndex));
	}
	else if (baseColor.b > 0.0) 
	{
		float colorIndex = 0.67;
		float shadeIndex = 0.5 - baseColor.b / 2;
		shadeIndex += increaseAmt;

		baseColor = texture(u_Palette, vec2(shadeIndex, colorIndex));
	}
	else if (baseColor.a > 0.0)
	{
		baseColor = texture(u_Palette, vec2(0.99, 0.0));
	}

	return baseColor;
}


void main()
{
	vec2 uv = v_TexCoord;
	vec4 baseColor = texture(u_Texture, uv);
	frag_Color = paletteSwap(baseColor);
	
}