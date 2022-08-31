#version 330 core
out vec4 FragColor;

// input the current position from the vertex shader for light calculations
in vec3 currentPos;
// input the normal vectors from the vertex shader
in vec3 normal;
// input the colour from the vertex shader
in vec3 color;
// input the texture coords from the vertex shader
in vec2 textureCoord;

uniform sampler2D diffuse0; // actual texture

uniform vec3 cameraPos;

void main()
{
	FragColor = texture(diffuse0, textureCoord);
}