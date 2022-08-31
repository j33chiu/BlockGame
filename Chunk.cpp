#include "Chunk.h"

Chunk::Chunk() {
	id = { 0, 0 };
	position = glm::vec2(0.0f, 0.0f);
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				blockMap[i][j][k] = -1;
			}
		}
	}
}

Chunk::Chunk(ChunkId id) {
	Chunk::id = id;
	position = glm::vec2(id.x * 16, id.z * 16);
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				blockMap[i][j][k] = -1;
			}
		}
	}
}

void Chunk::insertBlock(int x, int y, int z, short blockId) {
	blockMap[y][z][x] = blockId;
}

void Chunk::addTopFace(glm::vec3 blockPos, int blockId) {
	unsigned int indStart = meshVertVec.size();
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  1.0f,  0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  1.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) });
	
	meshIndVec.insert(meshIndVec.end(), { indStart + 0, indStart + 3, indStart + 2, indStart + 0, indStart + 1, indStart + 3 });
}

void Chunk::addFrontFace(glm::vec3 blockPos, int blockId) {
	unsigned int indStart = meshVertVec.size();
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  1.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE0) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE1) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE2) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  0.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE3) });

	meshIndVec.insert(meshIndVec.end(), { indStart + 0, indStart + 3, indStart + 2, indStart + 0, indStart + 1, indStart + 3 });
}

void Chunk::addLeftFace(glm::vec3 blockPos, int blockId) {
	unsigned int indStart = meshVertVec.size();
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE0) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE1) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  0.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE2) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE3) });

	meshIndVec.insert(meshIndVec.end(), { indStart + 0, indStart + 3, indStart + 2, indStart + 0, indStart + 1, indStart + 3 });

}

void Chunk::addBackFace(glm::vec3 blockPos, int blockId) {
	unsigned int indStart = meshVertVec.size();
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE0) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE1) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE2) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  0.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE3) });

	meshIndVec.insert(meshIndVec.end(), { indStart + 0, indStart + 3, indStart + 2, indStart + 0, indStart + 1, indStart + 3 });
}

void Chunk::addRightFace(glm::vec3 blockPos, int blockId) {
	unsigned int indStart = meshVertVec.size();
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE0) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  1.0f,  0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE1) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  0.0f,  1.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE2) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::SIDE3) });

	meshIndVec.insert(meshIndVec.end(), { indStart + 0, indStart + 3, indStart + 2, indStart + 0, indStart + 1, indStart + 3 });
}

void Chunk::addBottomFace(glm::vec3 blockPos, int blockId) {
	unsigned int indStart = meshVertVec.size();
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(0.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) });
	meshVertVec.push_back(Vertex{ blockPos + glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) });

	meshIndVec.insert(meshIndVec.end(), { indStart + 0, indStart + 3, indStart + 2, indStart + 0, indStart + 1, indStart + 3 });
}

void Chunk::generateMesh(Chunk* northChunk, Chunk* eastChunk, Chunk* southChunk, Chunk* westChunk) {
	// generate mesh for fast rendering
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 16; k++) {
				int blockId = blockMap[i][j][k];
				glm::vec3 blockPos = glm::vec3(k, i, j) + glm::vec3(position.x, 0, position.y);
				if (blockMap[i][j][k] == -1) {
					continue;
				}
				// for each block face check if adjacent block is transparent
				// top face
				if (i + 1 == 128) {
					// add top face
					addTopFace(blockPos, blockId);
				}
				else if (blockMap[i + 1][j][k] == -1) {
					// add top face
					addTopFace(blockPos, blockId);
				}
				// front face
				if (j + 1 == 16) {
					// check neighbouring chunk (in +ve z direction)
					if (eastChunk != nullptr && eastChunk->blockMap[i][0][k] == -1);
						//addFrontFace(blockPos, blockId);
				}
				else if (blockMap[i][j + 1][k] == -1) {
					// add front face
					addFrontFace(blockPos, blockId);
				}
				// left face
				if (k - 1 == -1) {
					// check neighbouring chunk
					if (southChunk != nullptr && southChunk->blockMap[i][j][15] == -1);
						//addLeftFace(blockPos, blockId);
				}
				else if (blockMap[i][j][k - 1] == -1) {
					// add left face
					addLeftFace(blockPos, blockId);
				}
				// back face
				if (j - 1 == -1) {
					// check neighbouring chunk
					if (westChunk != nullptr && westChunk->blockMap[i][15][k] == -1);
						//addBackFace(blockPos, blockId);
				}
				else if (blockMap[i][j - 1][k] == -1) {
					// add back face
					addBackFace(blockPos, blockId);
				}
				// right face
				if (k + 1 == 16) {
					// check neighbouring chunk
					if (northChunk != nullptr && northChunk->blockMap[i][j][0] == -1);
						//addRightFace(blockPos, blockId);
				}
				else if (blockMap[i][j][k + 1] == -1) {
					// add right face
					addRightFace(blockPos, blockId);
				}
				// bottom face
				if (i - 1 == -1) {
					// add bottom face
					addBottomFace(blockPos, blockId);
				}
				else if (blockMap[i - 1][j][k] == -1) {
					// add bottom face
					addBottomFace(blockPos, blockId);
				}
			}
		}
	}

	Texture t[] = {
		atlas.getAtlasForBlock(0)
	};
	meshTexVec = std::vector<Texture>(t, t + sizeof(t) / sizeof(Texture));

	// bind VAO to make it the current vertex array object
	VAO.Bind();
	// generate VBO, bind it, and link the vertices for the planks
	VBO VBO(meshVertVec);
	// generate EBO, bind it, and link the indices
	EBO EBO(meshIndVec);

	// link VBO to VAO (configure VAO so openGL knows how to read the VBO)
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // link (x, y, z)
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // link (normalx, normaly, normalz)
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // link (r, g, b)
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // link (texturex, texturey)

	// unbind everything to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	// delete since no longer needed
	VBO.Delete();
	EBO.Delete();
}

void Chunk::draw(Shader& shader, Camera& camera) {
	// sets current shader program
	shader.Activate();

	// bind the VAO:
	VAO.Bind();

	// handle textures
	unsigned int numDiffuse = 0; // actual textures
	unsigned int numSpecular = 0; // specular map textures

	// for each textures, determine type (diffuse or specular) and handle accordingly
	for (unsigned int i = 0; i < meshTexVec.size(); i++) {
		Texture t = meshTexVec[i];

		std::string num;
		std::string type = t.type;

		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}

		meshTexVec[i].texUnit(shader, (type + num).c_str());
		meshTexVec[i].Bind();
	}

	// export camera position to the fragment shader for lighting
	glUniform3f(glGetUniformLocation(shader.ID, "cameraPos"), camera.position.x, camera.position.y, camera.position.z);
	// export camera matrix to the shader
	camera.exportMatrix(shader, "camMatrix");

	glm::mat4 matrix = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));


	// draw the elements using primitives
	glDrawElements(GL_TRIANGLES, meshIndVec.size(), GL_UNSIGNED_INT, 0);
}

void Chunk::load() {

}

void Chunk::unload() {
	meshVertVec.clear();
	meshIndVec.clear();
	VAO.Delete();
}