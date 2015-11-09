#include "LevelLoader.h"

#include "Level.h"
#include "GameConstants.h"
#include "MainGame.h"
#include "Path.h"
#include "Log.h"

#include <fstream>


LevelLoader::LevelLoader(MainGame* mainGame,
	TextureLoader* textureLoader,
	LevelMap* levelMap)
	:_mainGame(mainGame),
	textureLoader_(textureLoader),
	_levelMap(levelMap),
	enemyBuilder_(textureLoader)
{
}


LevelLoader::~LevelLoader()
{
}

Level& LevelLoader::getLevel(const std::string& relativePath, TextureSheet* tileSet)
{

	if (!_loadedLevels.count(relativePath))
	{
		auto level = _loadedLevels.insert({ relativePath, Level(_mainGame, textureLoader_, _levelMap) });
		level.first->second.setTileCreator(&tileCreator_);
		level.first->second.setEnemyBuilder(&enemyBuilder_);
		level.first->second.load(Path::getFullPath(relativePath), tileSet, &tileCreator_);
	}
	return _loadedLevels.at(relativePath);
}

void LevelLoader::loadTiles(const std::string& filepath, Level& level, TextureSheet* tileSet, TileCreator* creator)
{
	std::ifstream ifs(filepath); //should probably do more error checking
	if (!ifs)
		LOG_STREAM(std::cerr) << "Failed to load: " << filepath;

	ifs >> level._levelID;

	int blockWidth, blockHeight;
	ifs >> blockWidth >> blockHeight;

	int numRows = blockHeight * Constants::TILES_PER_BLOCK_HEIGHT;
	int numCols = blockWidth * Constants::TILES_PER_BLOCK_WIDTH;

	level.tileArrangement.rows = numRows;
	level.tileArrangement.cols = numCols;
	level.tileArrangement.tiles = std::vector<std::vector<Tile>> (numRows, std::vector<Tile>(numCols));

	for (int r = 0; r < numRows; ++r)
	{
		for (int c = 0; c < numCols; ++c)
		{
			int tileNum;
			ifs >> tileNum;
			level.tileArrangement.tiles[r][c] = creator->create(tileSet, tileNum, r, c);
		}
	}
}

void LevelLoader::loadEnemies(const std::string& filepath, Level& level)
{
	std::ifstream ifs(filepath);
	if (!ifs)
		LOG_STREAM(std::cerr) << "Failed to load: " << filepath;

	std::string enemyName;
	Point pos;

	while (ifs >> enemyName >> pos.x >> pos.y)
	{
		level.addEnemyAtLocation(enemyName, pos);
	}

}