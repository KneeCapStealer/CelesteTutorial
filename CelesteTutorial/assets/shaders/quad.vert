#version 430 core

layout (location = 0) out vec2 textureCoordsOut;

void main()
{
	vec2 verticies[6] = 
	{
		// Top Left
		vec2(-0.5, 0.5),
		// Bottom left
		vec2(-0.5, -0.5),
		// Top right
		vec2(0.5, 0.5),
		// Top right
		vec2(0.5, 0.5),
		// Bottom left
		vec2(-0.5, -0.5),
		// Bottom right
		vec2(0.5, -0.5)
	};

	float left = 0.0;
	float top = 0.0;
	float right = 16.0;
	float bottom = 16.0;

	vec2 textureCoords[] = 
	{
		vec2(left, top),
		vec2(left, bottom),
		vec2(right, top),
		vec2(right, top),
		vec2(left, bottom),
		vec2(right, bottom)
	};
	textureCoordsOut = textureCoords[gl_VertexID];

	gl_Position = vec4(verticies[gl_VertexID], 1.0, 1.0);
}