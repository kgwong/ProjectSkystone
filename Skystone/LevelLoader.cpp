#include "LevelLoader.h"

#include "Level.h"
#include "GameConstants.h"
#include "MainGame.h"
#include "Path.h"
#include "Log.h"

#include <fstream>

const std::string LevelLoader::LEVEL_FILEPATH_PREFIX = "Levels/Level";

LevelLoader::LevelLoader(TextureLoader* textureLoader)
	:textureLoader_(textureLoader),
	enemyBuilder_(textureLoader),
	tileBuilder_(textureLoader)
{
}


LevelLoader::~LevelLoader()
{
}

void LevelLoader::setLevelManager(LevelManager* levelManager)
{
	levelManager_ = levelManager;
}

Level& LevelLoader::getLevelWithID(int levelID)
{
	if (!levelLoaded(levelID))
		load(levelID);
	return loadedLevels_.at(levelID);
}

bool LevelLoader::levelLoaded(int levelID)
{
	return loadedLevels_.count(levelID) > 0;
}

void LevelLoader::load(int levelID)
{
	Level level(levelID, textureLoader_);
	level.setLevelManager(levelManager_);
	level.setTileBuilder(&tileBuilder_);
	level.setEnemyBuilder(&enemyBuilder_);
	loadEnemies(generateFilePath("Enemies", levelID), level);
	loadTiles(generateFilePath("Tiles", levelID), level);

	loadedLevels_.insert({levelID, level});
}

std::string LevelLoader::generateFilePath(const std::string & tag, int levelID)
{
	std::string id = std::to_string(levelID); 
	return Path::getFullPath(LEVEL_FILEPATH_PREFIX + id + tag);
}

void LevelLoader::loadTiles(const std::string& filepath, Level& level)
{
	std::ifstream ifs(filepath); //should probably do more error checking
	if (!ifs)
		LOG_STREAM(std::cerr) << "Failed to load: " << filepath;

	int blockWidth, blockHeight;
	ifs >> blockWidth >> blockHeight;

	int numRows = blockHeight * Constants::TILES_PER_BLOCK_HEIGHT;
	int numCols = blockWidth * Constants::TILES_PER_BLOCK_WIDTH;

	level.tileArrangement.rows = numRows;
	level.tileArrangement.cols = numCols;
	level.tileArrangement.tiles = std::vector<std::vector<Tile>>(numRows, std::vector<Tile>(numCols));

	for (int r = 0; r < numRows; ++r)
	{
		for (int c = 0; c < numCols; ++c)
		{
			int tileNum;
			ifs >> tileNum;
			level.addTileAtLocation(tileNum, Point{ c * Constants::TILE_SIZE, r * Constants::TILE_SIZE });
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
