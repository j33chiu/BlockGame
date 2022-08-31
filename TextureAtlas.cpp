#include "TextureAtlas.h"

TextureAtlas::TextureAtlas() {
	Texture textures[] = {
		Texture("terrain1.png", "diffuse", 0) // 512px width, 256px height
	};
	textureAtlases = std::vector<Texture>(textures, textures + sizeof(textures) / sizeof(Texture));

	blockList.push_back(BlockInfo{ 0, "Bedrock", "terrain1.png", false, {0, -1}, {14, -1} });
	blockList.push_back(BlockInfo{ 1, "stone", "terrain1.png", false, {19, -1}, {15, -1} });
	blockList.push_back(BlockInfo{ 2, "dirt", "terrain1.png", false, {11, -1}, {14, -1} });
	blockList.push_back(BlockInfo{ 3, "grass", "terrain1.png", true, {2, 3}, {15, 15} });

}

std::vector<std::vector<int>> lookupBlocks;

glm::vec2 TextureAtlas::getTexCoordForBlock(int blockId, BlockCorner corner) {
	// terrain1: 512 by 256px

	// test terrain1 texture
	/*
	switch (corner) {
	case BlockCorner::TOP0:
		return glm::vec2(0, 1);
	case BlockCorner::TOP1:
		return glm::vec2(0.5, 1);
	case BlockCorner::TOP2:
		return glm::vec2(0, 0);
	case BlockCorner::TOP3:
		return glm::vec2(0.5, 0);
	case BlockCorner::SIDE0:
		return glm::vec2(0, 1);
	case BlockCorner::SIDE1:
		return glm::vec2(0.5, 1);
	case BlockCorner::SIDE2:
		return glm::vec2(0, 0);
	case BlockCorner::SIDE3:
		return glm::vec2(0.5, 1);
	default:
		return glm::vec2(0.0f, 0.0f);
	}*/

	
	BlockInfo blockInfo = blockList[blockId];
	float offsetX = 1.0f / 32.0f; // 32 textures horizontally in terrain1
	float offsetY = 1.0f / 16.0f; // 16 textures vertically in terrain1

	switch (corner) {
	case BlockCorner::TOP0:
		return glm::vec2((float)blockInfo.gridX[0] * offsetX, (float)(blockInfo.gridY[0] + 1) * offsetY);
	case BlockCorner::TOP1:
		return glm::vec2((float)(blockInfo.gridX[0] + 1) * offsetX, (float)(blockInfo.gridY[0] + 1) * offsetY);
	case BlockCorner::TOP2:
		return glm::vec2((float)blockInfo.gridX[0] * offsetX, (float)blockInfo.gridY[0] * offsetY);
	case BlockCorner::TOP3:
		return glm::vec2((float)(blockInfo.gridX[0] + 1) * offsetX, (float)blockInfo.gridY[0] * offsetY);
	case BlockCorner::SIDE0:
		if (blockInfo.multipleTextures)
			return glm::vec2((float)blockInfo.gridX[1] * offsetX, (float)(blockInfo.gridY[1] + 1) * offsetY);
		return glm::vec2((float)blockInfo.gridX[0] * offsetX, (float)(blockInfo.gridY[0] + 1) * offsetY);
	case BlockCorner::SIDE1:
		if (blockInfo.multipleTextures)
			return glm::vec2((float)(blockInfo.gridX[1] + 1) * offsetX, (float)(blockInfo.gridY[1] + 1) * offsetY);
		return glm::vec2((float)(blockInfo.gridX[0] + 1) * offsetX, (float)(blockInfo.gridY[0] + 1) * offsetY);
	case BlockCorner::SIDE2:
		if (blockInfo.multipleTextures)
			return glm::vec2((float)blockInfo.gridX[1] * offsetX, (float)blockInfo.gridY[1] * offsetY);
		return glm::vec2((float)blockInfo.gridX[0] * offsetX, (float)blockInfo.gridY[0] * offsetY);
	case BlockCorner::SIDE3:
		if (blockInfo.multipleTextures)
			return glm::vec2((float)(blockInfo.gridX[1] + 1) * offsetX, (float)blockInfo.gridY[1] * offsetY);
		return glm::vec2((float)(blockInfo.gridX[0] + 1) * offsetX, (float)blockInfo.gridY[0] * offsetY);
	default:
		return glm::vec2(0.0f, 0.0f);
	}
}

glm::vec2 TextureAtlas::getTexCoordForItem(int itemId) {
	return glm::vec2(0.0f, 0.0f);
}

Texture TextureAtlas::getAtlasForBlock(int blockId) {
	return textureAtlases[0];
}

Texture TextureAtlas::getAtlasForItem(int blockId) {
	return textureAtlases[0];
}