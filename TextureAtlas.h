#ifndef TEXTURE_ATLAS_CLASS_H
#define TEXTURE_ATLAS_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

#include "Texture.h"

enum class BlockCorner {
		TOP0, TOP1, TOP2, TOP3,
		SIDE0, SIDE1, SIDE2, SIDE3
	};

struct BlockInfo {
	int id;
	std::string name;
	std::string textureName;
	bool multipleTextures = false;
	// elements in order of top view, then side block view
	int gridX[2];
	int gridY[2];
};

class TextureAtlas {
public:
	std::vector<Texture> textureAtlases;

	std::vector<BlockInfo> blockList;

	// load all atlases
	TextureAtlas();

	// get texcoords
	glm::vec2 getTexCoordForBlock(int blockId, BlockCorner corner);
	glm::vec2 getTexCoordForItem(int itemId);

	Texture getAtlasForBlock(int blockId);
	Texture getAtlasForItem(int itemId);
};

#endif
