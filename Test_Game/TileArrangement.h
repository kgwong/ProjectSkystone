#ifndef TILE_ARRANGEMENT_H
#define TILE_ARRANGEMENT_H	

#include "TileSet.h"
#include "Tile.h"

struct TileArrangement
{
	TileArrangement(){};
	TileArrangement(std::vector<std::vector<Tile>> tiles, int tileSize, int rows, int cols)
		:_tiles(tiles), _tileSize(tileSize), _rows(rows), _cols(cols){};

	std::vector<std::vector<Tile>> _tiles;
	int _tileSize;
	int _rows;
	int _cols;
};

#endif //TILE_ARRANGEMENT_H

