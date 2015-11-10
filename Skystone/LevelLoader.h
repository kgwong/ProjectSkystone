#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>
#include <map>

#include "TextureSheet.h"
#include "TileCreator.h"
#include "EnemyBuilder.h"

class Level;
class MainGame;
class TextureLoader;
class LevelMap;
class LevelManager;

class LevelLoader
{
public:
	LevelLoader(MainGame* mainGame,
		TextureLoader* textureLoader,
		LevelMap* levelMap);
	~LevelLoader();

	void setLevelManager(LevelManager* levelManager);

	Level& getLevel(const std::string& relativePath, 
						TextureSheet* tileSet);

public:
	static void loadTiles(const std::string& filepath, Level& level, TextureSheet* tileSet, TileCreator* creator);
	static void loadEnemies(const std::string& filepath, Level& level);

private:
	MainGame* _mainGame;
	TextureLoader* textureLoader_;
	LevelManager* levelManager_;
	LevelMap* _levelMap;

	TileCreator tileCreator_;
	EnemyBuilder enemyBuilder_;

	std::map<std::string, Level> _loadedLevels;


};

#endif //LEVEL_LOADER_H

