#include "Texture.h"

Texture::Texture(const char* imageFile, const char* texType, GLuint slot) {
	type = texType;
	unit = slot;

	int texW, texH, nColourChan;

	// since stbi and openGL read images in opposite (vertical) directions
	stbi_set_flip_vertically_on_load(true);
	unsigned char* texBytes = stbi_load(imageFile, &texW, &texH, &nColourChan, 0);

	// generate 1 texture with the current Texture object ID
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEAREST for pixel art, GL_LINEAR for blurred when scaling up
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// repeat textures if something goes wrong
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // s axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // t axis

	// generate image
	if (nColourChan == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGBA, GL_UNSIGNED_BYTE, texBytes);
	}
	else if (nColourChan == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGB, GL_UNSIGNED_BYTE, texBytes);
	}
	else if (nColourChan == 1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RED, GL_UNSIGNED_BYTE, texBytes);
	}
	else {
		throw std::invalid_argument("Automatic Texture type recognition failed: invalid number of colour channels.");
	}

	// generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(texBytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform) {
	// set uniforms in shader to the correct texture unit, so shader uses the correct texture
	GLuint uniformTex = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(uniformTex, unit);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}