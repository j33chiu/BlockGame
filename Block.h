#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <glad/glad.h>

#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "Vertex.h"
#include "TextureAtlas.h"
#include "Camera.h"

class Block {
public:
	glm::vec3 position;
	int blockId;

	// in order of top, front, left, back, right, bottom
	bool renderFace[6] = { true, true, true, true, true, true};

	VAO VAO;

	Block(glm::vec3 position);
	Block(glm::vec3 position, int blockId, TextureAtlas& atlas);

	void update(glm::vec3 position, int blockId, TextureAtlas& atlas);
	void updateInd(std::vector<GLuint>& updateIndices);

	bool isAir();
	void draw(Shader& shader, Camera& camera);

	std::vector<Vertex> blockVertVec;
	std::vector<GLuint> blockIndVec;
	std::vector<Texture> blockTexVec;
};

#endif