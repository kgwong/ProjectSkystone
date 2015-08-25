#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>
#include <map>

#include "TextureSheet.h"
#include "TileCreator.h"

class Level;
class MainGame;
class TextureLoader;
class LevelMap;


class LevelLoader
{
public:
	LevelLoader(MainGame* mainGame,
		TextureLoader* textureLoader,
		LevelMap* levelMap);
	~LevelLoader();

	Level& getLevel(const std::string& filepath, TextureSheet* tileSet, TileCreator* creator);

public:
	static void loadTiles(const std::string& filepath, Level& level, TextureSheet* tileSet, TileCreator* creator);
	static void loadEnemies(const std::string& filepath, Level& level);

private:
	MainGame* _mainGame;
	TextureLoader* textureLoader_;
	LevelMap* _levelMap;

	std::map<std::string, Level> _loadedLevels;


};

#endif //LEVEL_LOADER_H

