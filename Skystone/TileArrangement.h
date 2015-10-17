#ifndef TILE_ARRANGEMENT_H
#define TILE_ARRANGEMENT_H	

#include "Tile.h"

struct TileArrangement
{
	std::vector<std::vector<Tile>> tiles;
	int rows;
	int cols;
};

#endif //TILE_ARRANGEMENT_H

