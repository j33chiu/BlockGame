#version 330 core
layout (location = 0) in vec3 aPos; // positions/coordinates
layout (location = 1) in vec3 aNorm; // normal vector
layout (location = 2) in vec3 aColor; // colours
layout (location = 3) in vec2 aTex; // texture coordinates


// outputs the current position for the fragment shader
out vec3 currentPos;
// outputs normal vector
out vec3 normal;
// outputs colours for the fragment shader
out vec3 color;
// outputs texture
out vec2 textureCoord;

uniform mat4 camMatrix;

uniform mat4 model;


void main()
{
	// assign outputs
	currentPos = vec3(model * vec4(aPos, 1.0f));
	normal = aNorm;
	color = aColor;
	textureCoord = aTex;

	gl_Position = camMatrix * vec4(currentPos, 1.0);
}