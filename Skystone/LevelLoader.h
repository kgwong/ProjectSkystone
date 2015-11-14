#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>
#include <map>

#include "TextureSheet.h"
#include "TileCreator.h"
#include "EnemyBuilder.h"
#include "TileBuilder.h"

class Level;
class TextureLoader;
class LevelMap;
class LevelManager;

class LevelLoader
{
public:
	static const std::string LEVEL_FILEPATH_PREFIX;

public:
	LevelLoader(TextureLoader* textureLoader);
	~LevelLoader();

	void setLevelManager(LevelManager* levelManager);
	
	Level& getLevelWithID(int levelID);
	Level& getLevel(const std::string& relativePath, 
						TextureSheet* tileSet);

public:
	static void loadTiles(const std::string& filepath, Level& level, TextureSheet* tileSet, TileCreator* creator);
	static void loadEnemies(const std::string& filepath, Level& level);

private:
	TextureLoader* textureLoader_;
	LevelManager* levelManager_;

	TileCreator tileCreator_;
	EnemyBuilder enemyBuilder_;
	TileBuilder tileBuilder_;

	std::map<std::string, Level> _loadedLevels;
	std::map<int, Level> loadedLevels2;

private:
	bool levelLoaded(int levelID);
	void load(int levelID);

	std::string generateFilePath(const std::string& tag, int levelID);

	void loadEnemies2(const std::string& filepath, Level& level);
	void loadTiles2(const std::string& filepath, Level& level);


};

#endif //LEVEL_LOADER_H

