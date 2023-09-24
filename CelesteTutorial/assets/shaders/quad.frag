#version 430 core

layout (location = 0) in vec2 textureCoordsIn;

layout (location = 0) out vec4 fragColor;

layout (location = 0) uniform sampler2D textureAtlas;

void main()
{
	vec4 texureColor = texelFetch(textureAtlas, ivec2(textureCoordsIn), 0);

	if (texureColor.a == 0)
		discard;

	// White
	fragColor = texureColor;
}