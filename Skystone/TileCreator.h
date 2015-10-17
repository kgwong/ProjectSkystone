#ifndef TILE_CREATOR_H
#define TILE_CREATOR_H

#include "Tile.h"

class TileCreator
{
public:
	TileCreator(GameWindow* window);
	~TileCreator();

	Tile create(TextureSheet* textureSheet,
		int tileIndex, int r, int c);

private:
	GameWindow* window_;
};

#endif //TILE_CREATOR_H