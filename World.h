#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <vector>
#include <unordered_map>

#include "Player.h"
#include "Chunk.h"

enum class WorldType {
	SUPERFLAT,
	NORMAL
};

class World {
public:
	WorldType type;
	int seed;

	std::unordered_map<std::string, ChunkId> playerChunks;
	std::unordered_map<std::string, Player*> players; // determines which chunks are loaded

	std::unordered_map<ChunkId, Chunk*> chunkMap;

	World(WorldType type, int seed = 123456789);

	void addPlayer(Player& player);
	void playersUpdated();
	void updateLoadedChunks();

	void loadChunk(Chunk& chunk);
	void generateChunk(Chunk& chunk);
	void renderChunk(Chunk& chunk);

	void draw(Shader& shader, Camera& camera, TextureAtlas& atlas, Block& drawingBlock);

	void playerTick();

	~World();
};

#endif