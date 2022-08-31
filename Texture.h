#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture {
public:
	GLuint ID;
	const char* type; // whether it is diffuse or specular
	GLuint unit; // for multiple textures

	Texture(const char* imageFile, const char* texType, GLuint slot);

	void texUnit(Shader& shader, const char* uniform);
	void Bind();
	void Unbind();
	void Delete();
};

#endif

