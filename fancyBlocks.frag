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

uniform vec4 lightColour;
uniform vec3 lightPos;

uniform vec3 cameraPos;

vec4 pointLight() {
	// realistically, light will bounce off objects, but this is computationally expensive, so for now, use ambient light (base light value)
	float ambientLight = 0.20f;
	
	// normalize light direction vector
	vec3 normalizedNorm = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currentPos);

	// diffused lighting method
	float diffuse = max(dot(normalizedNorm, lightDirection), 0.0f);

	// specular light
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(cameraPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normalizedNorm);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, textureCoord) * lightColour * (diffuse + ambientLight + specular)); // simulate the colour of the object in a given light

}

// near and far planes should be the same as those specified in the camera class
float near = 0.1f;
float far = 100.0f;

vec4 depthView() {
	// colour of object is grayscale between 0.0 (near plane) and 1.0 (far plane) based on distance from camera
	// note that depth is not linear in openGL, so objects at mid and long range almost always be pure white
	return vec4(vec3(gl_FragCoord.z), 1.0f);
}

vec4 linearizedDepthView(float depth) {
	// object will be black when near, white when far
	float value = (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));

	return vec4(vec3(value / far), 1.0f);
}

float logisticDepth(float depth, float steepness = 0.5f, float offset = 5.0f) {
	// helps smoothen edges of vision, and can help create a fog effect
	float zVal = (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));

	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
	// use logistic depth for fog effect on the bricks
	float depth = logisticDepth(gl_FragCoord.z);
	FragColor = pointLight() * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}