#ifndef TILE_CREATOR_H
#define TILE_CREATOR_H

#include "Tile.h"

class TileCreator
{
public:
	TileCreator();
	~TileCreator();

	Tile create(TextureSheet* textureSheet,
		int tileIndex, int r, int c);
};

#endif //TILE_CREATOR_H