#include "LevelLoader.h"

#include "Level.h"
#include "MainGame.h"

#include <fstream>

void LevelLoader::loadTiles(const std::string& filepath, Level& level, TileSet* tileSet)
{
	std::ifstream ifs(filepath); //should probably do more error checking
	if (!ifs)
		std::cout << "Failed to load: " << filepath << std::endl;

	int numRows, numCols;
	ifs >> numCols >> numRows;

	level.tileArrangement.rows = numRows;
	level.tileArrangement.cols = numCols;
	level.tileArrangement.tiles = std::vector<std::vector<Tile>> (numRows, std::vector<Tile>(numCols));

	for (int r = 0; r < numRows; ++r)
	{
		for (int c = 0; c < numCols; ++c)
		{
			int tileNum;
			ifs >> tileNum;
			level.tileArrangement.tiles[r][c] = tileSet->createTile(tileNum, r, c);
		}
	}
}

void LevelLoader::loadEnemies(const std::string& filepath, Level& level)
{
	std::ifstream ifs(filepath);
	if (!ifs)
		std::cout << "Failed to load: " << filepath << std::endl;

	std::string enemyName;
	Point pos;

	while (ifs >> enemyName >> pos.x >> pos.y)
	{
		level.addEnemyAtLocation(enemyName, pos);
	}

}