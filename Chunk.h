#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "Block.h"

struct ChunkId {
	int x;
	int z;

	bool operator==(const ChunkId &chunkId) const {
		return x == chunkId.x && z == chunkId.z;
	}

	bool operator!=(const ChunkId &chunkId) const {
		return x != chunkId.x || z != chunkId.z;
	}
};

// hash function for using ChunkID as a key in k-v pair
template<>
struct std::hash<ChunkId>
{
	std::size_t operator()(const ChunkId& chunkId) const {
		// Compute individual hash values for first, second and third
			// http://stackoverflow.com/a/1646913/126995
		size_t res = 17;
		res = res * 31 + hash<int>()(chunkId.x);
		res = res * 31 + hash<int>()(chunkId.z);
		return res;
		/*
		using std::size_t;
		using std::hash;
		return ((hash<int>()(chunkId.x)
			^ (hash<int>()(chunkId.z) << 1)) >> 1);*/
	};
};

class Chunk {
public:

	glm::vec2 position;
	ChunkId id;

	Chunk();
	Chunk(ChunkId id);

	// in (y, z, x) coords
	short blockMap[128][16][16];
	std::vector<Vertex> meshVertVec;
	std::vector<GLuint> meshIndVec;
	std::vector<Texture> meshTexVec;

	VAO VAO;
	TextureAtlas atlas;

	void draw(Shader& shader, Camera& camera);

	void insertBlock(int x, int y, int z, short blockId);

	void addTopFace(glm::vec3 blockPos, int blockId);
	void addFrontFace(glm::vec3 blockPos, int blockId);
	void addLeftFace(glm::vec3 blockPos, int blockId);
	void addBackFace(glm::vec3 blockPos, int blockId);
	void addRightFace(glm::vec3 blockPos, int blockId);
	void addBottomFace(glm::vec3 blockPos, int blockId);
	void generateMesh(Chunk* northChunk, Chunk* eastChunk, Chunk* southChunk, Chunk* westChunk);
	
	void load();
	void unload();
};

#endif