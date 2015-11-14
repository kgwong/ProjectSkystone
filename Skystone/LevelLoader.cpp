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
	return loadedLevels2.at(levelID);
}

Level& LevelLoader::getLevel(const std::string& relativePath, TextureSheet* tileSet)
{

	if (!_loadedLevels.count(relativePath))
	{ //UGLY!!!
		auto level = _loadedLevels.insert({ relativePath, Level(textureLoader_) });
		level.first->second.setLevelManager(levelManager_);
		level.first->second.setTileCreator(&tileCreator_);
		level.first->second.setEnemyBuilder(&enemyBuilder_);
		level.first->second.setTileBuilder(&tileBuilder_);
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

bool LevelLoader::levelLoaded(int levelID)
{
	return loadedLevels2.count(levelID);
}

void LevelLoader::load(int levelID)
{
	Level level(textureLoader_);
	level.setLevelManager(levelManager_);
	level.setTileBuilder(&tileBuilder_);
	level.setEnemyBuilder(&enemyBuilder_);
	loadEnemies2(generateFilePath("Enemies", levelID), level);
	loadTiles2(generateFilePath("Tiles", levelID), level);

	loadedLevels2.insert({levelID, level});
}

std::string LevelLoader::generateFilePath(const std::string & tag, int levelID)
{
	std::string id = std::to_string(levelID); 
	return Path::getFullPath(LEVEL_FILEPATH_PREFIX + id + tag);
}

void LevelLoader::loadTiles2(const std::string& filepath, Level& level)
{
	std::ifstream ifs(filepath); //should probably do more error checking
	if (!ifs)
		LOG_STREAM(std::cerr) << "Failed to load: " << filepath;


	std::cout << "LEVEL: " << filepath << std::endl;
	//ifs >> level._levelID;

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
			//level.tileArrangement.tiles[r][c] = creator->create(tileSet, tileNum, r, c);
		}
	}
}

void LevelLoader::loadEnemies2(const std::string& filepath, Level& level)
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
