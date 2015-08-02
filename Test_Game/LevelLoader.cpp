#include "LevelLoader.h"

#include <fstream>

TileArrangement LevelLoader::load(const std::string& filepath, TileSet* tileSet)
{
	std::ifstream ifs(filepath); //should probably do more error checking
	if (ifs == nullptr)
		std::cout << "Loading Level failed!" << std::endl;

	int numRows, numCols;
	ifs >> numCols >> numRows;

	std::vector<std::vector<Tile>> tiles(numRows, std::vector<Tile>(numCols));

	for (int r = 0; r < numRows; ++r)
	{
		for (int c = 0; c < numCols; ++c)
		{
			int tileNum;
			ifs >> tileNum;
			tiles[r][c] = tileSet->createTile(tileNum, r, c);
		}
	}

	return TileArrangement(tiles, tileSet->getTileSize(), numRows, numCols);
}
