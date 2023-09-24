#version 430 core

// Structs
struct Transform
{
	vec2 pos;
	vec2 size;
	ivec2 atlasOffset;
	ivec2 spriteSize;
};

// Input
layout (std430, binding = 0) buffer TransformSBO
{
	Transform transforms[];
};

uniform vec2 screenSize;

// Output
layout (location = 0) out vec2 textureCoordsOut;

void main()
{
	Transform transform = transforms[gl_InstanceID];

	vec2 verticies[6] = 
	{
		transform.pos,									// Top Left
		transform.pos + vec2(0.0, transform.size.y),	// Bottom Left
		transform.pos + vec2(transform.size.x, 0.0),	// Top Right
		transform.pos + vec2(transform.size.x, 0.0),	// Top Right
		transform.pos + vec2(0.0, transform.size.y),	// Bottom Left
		transform.pos + transform.size					// Bottom Right
	};

	float left = transform.atlasOffset.x;
	float top = transform.atlasOffset.y;
	float right = transform.atlasOffset.x + transform.spriteSize.x;
	float bottom = transform.atlasOffset.y + transform.spriteSize.y;

	vec2 textureCoords[] = 
	{
		vec2(left, top),
		vec2(left, bottom),
		vec2(right, top),
		vec2(right, top),
		vec2(left, bottom),
		vec2(right, bottom)
	};

	// normalize postion
	{
		vec2 vertexPos = verticies[gl_VertexID];
		vertexPos.y = -vertexPos.y + screenSize.y;
		vertexPos = 2.0 * (vertexPos / screenSize) - 1.0;
		gl_Position = vec4(vertexPos, 1.0, 1.0);
	}

	textureCoordsOut = textureCoords[gl_VertexID];
}