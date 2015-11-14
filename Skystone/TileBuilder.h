#ifndef TILE_BUILDER_H
#define TILE_BUILDER_H

#include <string>
#include "Tile.h"

class TextureLoader;

class TileBuilder
{
public:
	TileBuilder(TextureLoader* textureLoader);
	~TileBuilder();

	Tile* build(int tileType, Tile& tileToBuild);

private:
	TextureLoader* textureLoader_;
};

#endif //TILE_BUILDER_H