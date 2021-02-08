#version 330 core

// runs on each pixel
// what color do you want this pixel to be

layout(location = 0) out vec4 frag_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Palette;

uniform float u_Time;
uniform float u_Fade;

vec4 paletteSwap(vec4 baseColor) 
{

	float increaseAmt = 0.5 - u_Fade / 2.0;

	if (baseColor.r > 0.0) 
	{
		float colorIndex = 0.0; // y = 0
		float shadeIndex = 0.5 - baseColor.r / 2;
		shadeIndex += increaseAmt;

		baseColor = texture(u_Palette, vec2(shadeIndex, colorIndex));
	}
	else if (baseColor.g > 0.0) 
	{
		// TODO work out the exact number
		float colorIndex = 0.34; // y = 1
		float shadeIndex = 0.5 - baseColor.g / 2;
		shadeIndex += increaseAmt;

		baseColor = texture(u_Palette, vec2(shadeIndex, colorIndex));
	}
	else if (baseColor.b > 0.0) 
	{
		float colorIndex = 0.67; // y = 2
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