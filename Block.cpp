#include "Block.h"

Block::Block(glm::vec3 position) {
	// constructor for "empty" air block
	Block::position = position;
	Block::blockId = -1;
}

Block::Block(glm::vec3 position, int blockId, TextureAtlas& atlas) {
	Block::position = position;
	Block::blockId = blockId;

	// in order of coords, normals, colours, texcoords
	Vertex v[] = {
		// each face is in the order of:
		// 0 1
		// 2 3
		// when looking at the blockface
		// orientation: camera is looking in -ve z direction

		// top face
		Vertex{position + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0)},
		Vertex{position + glm::vec3( 1.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1)},
		Vertex{position + glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2)},
		Vertex{position + glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3)},
																		    	   
		// front face													    	   
		Vertex{position + glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0)},
		Vertex{position + glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1)},
		Vertex{position + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2)},
		Vertex{position + glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3)},
																		    	   
		// left face													    	   
		Vertex{position + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0)},
		Vertex{position + glm::vec3( 0.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1)},
		Vertex{position + glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2)},
		Vertex{position + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3)},

		// back face
		Vertex{position + glm::vec3( 1.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0)},
		Vertex{position + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1)},
		Vertex{position + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2)},
		Vertex{position + glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3)},

		// right face
		Vertex{position + glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0)},
		Vertex{position + glm::vec3( 1.0f,  1.0f,  0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1)},
		Vertex{position + glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2)},
		Vertex{position + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3)},

		// bottom face
		Vertex{position + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0)},
		Vertex{position + glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1)},
		Vertex{position + glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2)},
		Vertex{position + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3)}
	};
	blockVertVec = std::vector<Vertex>(v, v + sizeof(v) / sizeof(Vertex));

	GLuint i[] = {
		// top face
		0, 3, 2,
		0, 1, 3,
		// front face
		4, 7, 6,
		4, 5, 7,
		// left face
		8, 11, 10,
		8, 9, 11,
		// back face
		12, 15, 14,
		12, 13, 15,
		// right face
		16, 19, 18,
		16, 17, 19,
		// bottom face
		20, 23, 22,
		20, 21, 23
	};
	blockIndVec = std::vector<GLuint>(i, i + sizeof(i) / sizeof(GLuint));

	Texture t[] = {
		atlas.getAtlasForBlock(blockId)
	};
	blockTexVec = std::vector<Texture>(t, t + sizeof(t) / sizeof(Texture));


	// bind VAO to make it the current vertex array object
	VAO.Bind();
	// generate VBO, bind it, and link the vertices for the planks
	VBO VBO(blockVertVec);
	// generate EBO, bind it, and link the indices
	EBO EBO(blockIndVec);

	// link VBO to VAO (configure VAO so openGL knows how to read the VBO)
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // link (x, y, z)
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // link (normalx, normaly, normalz)
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // link (r, g, b)
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // link (texturex, texturey)

	// unbind everything to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Block::update(glm::vec3 position, int blockId, TextureAtlas& atlas) {
	Block::position.x = position.x;
	Block::position.y = position.y;
	Block::position.z = position.z;
	Block::blockId = blockId;

	// top face
	blockVertVec[0] = Vertex{ position + glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) };
	blockVertVec[1] = Vertex{ position + glm::vec3(1.0f,  1.0f,  0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) };
	blockVertVec[2] = Vertex{ position + glm::vec3(0.0f,  1.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) };
	blockVertVec[3] = Vertex{ position + glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) };
	// front face													    	   
	blockVertVec[4] = Vertex{ position + glm::vec3(0.0f,  1.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) };
	blockVertVec[5] = Vertex{ position + glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) };
	blockVertVec[6] = Vertex{ position + glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) };
	blockVertVec[7] = Vertex{ position + glm::vec3(1.0f,  0.0f,  1.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) };
	// left face													    	   
	blockVertVec[8] = Vertex{ position + glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) };
	blockVertVec[9] = Vertex{ position + glm::vec3(0.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) };
	blockVertVec[10] = Vertex{ position + glm::vec3(0.0f,  0.0f,  0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) };
	blockVertVec[11] = Vertex{ position + glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) };
	// back face
	blockVertVec[12] = Vertex{ position + glm::vec3(1.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) };
	blockVertVec[13] = Vertex{ position + glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) };
	blockVertVec[14] = Vertex{ position + glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) };
	blockVertVec[15] = Vertex{ position + glm::vec3(0.0f,  0.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) };
	// right face
	blockVertVec[16] = Vertex{ position + glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) };
	blockVertVec[17] = Vertex{ position + glm::vec3(1.0f,  1.0f,  0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) };
	blockVertVec[18] = Vertex{ position + glm::vec3(1.0f,  0.0f,  1.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) };
	blockVertVec[19] = Vertex{ position + glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) };
	// bottom face
	blockVertVec[20] = Vertex{ position + glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP0) };
	blockVertVec[21] = Vertex{ position + glm::vec3(1.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP1) };
	blockVertVec[22] = Vertex{ position + glm::vec3(0.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP2) };
	blockVertVec[23] = Vertex{ position + glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), atlas.getTexCoordForBlock(blockId, BlockCorner::TOP3) };

	// bind VAO to make it the current vertex array object
	VAO.Bind();
	// generate VBO, bind it, and link the vertices for the planks
	VBO VBO(blockVertVec);
	// generate EBO, bind it, and link the indices
	EBO EBO(blockIndVec);

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

void Block::updateInd(std::vector<GLuint>& ind) {
	blockIndVec.clear();
	blockIndVec.insert(blockIndVec.end(), ind.begin(), ind.end());
}

bool Block::isAir() {
	return blockId == -1;
}

void Block::draw(Shader& shader, Camera& camera) {
	if (blockId == -1) return; // don't render air
	// sets current shader program
	shader.Activate();

	// bind the VAO:
	VAO.Bind();

	// handle textures
	unsigned int numDiffuse = 0; // actual textures
	unsigned int numSpecular = 0; // specular map textures

	// for each textures, determine type (diffuse or specular) and handle accordingly
	for (unsigned int i = 0; i < blockTexVec.size(); i++) {
		Texture t = blockTexVec[i];
		
		std::string num;
		std::string type = t.type;

		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}

		blockTexVec[i].texUnit(shader, (type + num).c_str());
		blockTexVec[i].Bind();
	}

	// export camera position to the fragment shader for lighting
	glUniform3f(glGetUniformLocation(shader.ID, "cameraPos"), camera.position.x, camera.position.y, camera.position.z);
	// export camera matrix to the shader
	camera.exportMatrix(shader, "camMatrix");

	glm::mat4 matrix = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));


	// draw the elements using primitives
	glDrawElements(GL_TRIANGLES, blockIndVec.size(), GL_UNSIGNED_INT, 0);
}