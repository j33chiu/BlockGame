#include "World.h"

World::World(WorldType type, int seed) {
	World::type = type;
	World::seed = seed;
}

void World::addPlayer(Player &player) {
	players[player.name] = &player;
	playersUpdated();
}

void World::playersUpdated() {
	// updates which chunks should be loaded
	for (auto& it : players) {
		Player p = *(it.second);
		ChunkId playerChunk {
			std::floor((float)p.position.x / 16.0f),
			std::floor((float)p.position.z / 16.0f)
		};
		std::unordered_map<std::string, ChunkId>::const_iterator foundChunkId = playerChunks.find(p.name);
		if (foundChunkId == playerChunks.end()) {
			// not found, should generate and add to map (update loaded chunks)
			playerChunks[p.name] = playerChunk;
			updateLoadedChunks();
		}
		else if (foundChunkId->second != playerChunk) {
			// found, and player chunk is different, so need to update loaded chunks
			playerChunks[p.name] = playerChunk;
			updateLoadedChunks();
		}
	}
}

bool tooFar(ChunkId chunk, ChunkId playerChunk, int thresh) {
	int xDiff = abs(chunk.x - playerChunk.x);
	int zDiff = abs(chunk.z - playerChunk.z);
	if (xDiff > thresh || zDiff > thresh) return true;
	return false;
}

void World::updateLoadedChunks() {
	std::unordered_map<ChunkId, Chunk*>::iterator chunkMapIt = chunkMap.begin();
	while (chunkMapIt != chunkMap.end()) {
		ChunkId chunkId = chunkMapIt->first;
		Chunk* chunk = chunkMapIt->second;
		bool closeEnough = false;
		for (auto& playerChunksIt : playerChunks) {
			ChunkId playerChunkId = playerChunksIt.second;
			if (!tooFar(chunkId, playerChunkId, players[playerChunksIt.first]->chunkLoadDist)) {
				closeEnough = true;
				break;
			}
		}
		if (!closeEnough) {
			// unload the chunk
			chunk->unload();
			// remove the id and the chunk
			chunkMapIt = chunkMap.erase(chunkMapIt);
			delete chunk;
		}
		else {
			chunkMapIt++;
		}
	}
	for (auto& it : playerChunks) {
		ChunkId playerChunk = it.second;
		int playerChunkLoadDist = players[it.first]->chunkLoadDist;
		for (int x = playerChunk.x - playerChunkLoadDist; x <= playerChunk.x + playerChunkLoadDist; x++) {
			for (int z = playerChunk.z - playerChunkLoadDist; z <= playerChunk.z + playerChunkLoadDist; z++) {
				ChunkId newChunkId{ x, z };
				if (chunkMap.find(newChunkId) == chunkMap.end()) {
					// map does not contain chunkId as key
					Chunk* newChunk = new Chunk(newChunkId);
					chunkMap[newChunkId] = newChunk;
				}
			}
		}
	}
	std::unordered_map<ChunkId, Chunk*>::iterator chunkMapIt2 = chunkMap.begin();
	while (chunkMapIt2 != chunkMap.end()) {
		Chunk* chunk = chunkMapIt2->second;
		loadChunk(*chunk);
		chunkMapIt2++;
	}

	std::unordered_map<ChunkId, Chunk*>::iterator chunkMapIt3 = chunkMap.begin();
	while (chunkMapIt3 != chunkMap.end()) {
		Chunk* chunk = chunkMapIt3->second;
		renderChunk(*chunk);
		chunkMapIt3++;
	}
}

void World::loadChunk(Chunk& chunk) {
	// if not generated already, generate chunk

	// for now, chunks are not saved, so just generate
	generateChunk(chunk);
	// load chunk
}

void World::generateChunk(Chunk& chunk) {
	// generates chunk
	if (type == WorldType::SUPERFLAT) {
		// generates layer of grass on top of a layer of dirt on top of 3 layers of stone on top of a layer of bedrock
		//memset(chunk.blockMap, -1, sizeof(chunk.blockMap) / sizeof(short));
		for (int i = 0; i < 128; i++) {
			for (int j = 0; j < 16; j++) {
				for (int k = 0; k < 16; k++) {
					if (i == 0)
						chunk.insertBlock(k, i, j, 0); // bedrock
					else if (i == 1 || i == 2 || i == 3)
						chunk.insertBlock(k, i, j, 1); // stone
					else if (i == 4)
						chunk.insertBlock(k, i, j, 2); // dirt
					else if (i == 5)
						chunk.insertBlock(k, i, j, 3); // grass
				}
			}
		}
	}
	else if (type == WorldType::NORMAL) {
		// generate height map with values between [-1, 1] and use a variable for sea level

		// here, set sea level to be at y = 60
	}
}

void World::renderChunk(Chunk& chunk) {
	// adjacent chunks
	ChunkId northChunkId = { chunk.id.x + 1, chunk.id.z };
	Chunk* northChunk = nullptr;
	if (chunkMap.find(northChunkId) != chunkMap.end())
		northChunk = chunkMap[northChunkId];

	ChunkId eastChunkId = { chunk.id.x, chunk.id.z + 1 };
	Chunk* eastChunk = nullptr;
	if (chunkMap.find(eastChunkId) != chunkMap.end())
		eastChunk = chunkMap[eastChunkId];

	ChunkId southChunkId = { chunk.id.x - 1, chunk.id.z };
	Chunk* southChunk = nullptr;
	if (chunkMap.find(southChunkId) != chunkMap.end())
		southChunk = chunkMap[southChunkId];

	ChunkId westChunkId = { chunk.id.x, chunk.id.z - 1 };
	Chunk* westChunk = nullptr;
	if (chunkMap.find(westChunkId) != chunkMap.end())
		westChunk = chunkMap[westChunkId];

	chunk.generateMesh(northChunk, eastChunk, southChunk, westChunk);
}

void World::draw(Shader& shader, Camera& camera, TextureAtlas& atlas, Block& drawingBlock) {
	/*for (Chunk c : loadedChunks) {
		c.draw(shader, player.camera);
	}*/
	for (auto& it : chunkMap) {
		it.second->draw(shader, camera);
		//it.second->draw(shader, camera, atlas, drawingBlock);
	}
}

void World::playerTick() {

	playersUpdated();
}

World::~World() {
	// pointers in chunkmap must be deleted	
	std::unordered_map<ChunkId, Chunk*>::iterator chunkMapIt = chunkMap.begin();
	while(chunkMapIt != chunkMap.end()) {
		Chunk* chunk = chunkMapIt->second;
		chunkMapIt = chunkMap.erase(chunkMapIt);
		delete chunk;
	}
}
