#ifndef LOADED_LEVEL_CACHE_H
#define LOADED_LEVEL_CACHE_H

#include <string>
#include <map>


#include "Level.h"

class LoadedLevelCache
{
public:
	LoadedLevelCache(MainGame* mainGame,
			ResourceLocator* resourceLocator,
			LevelMap* levelMap);
	~LoadedLevelCache();

	Level& getLevel(const std::string& filepath, TileSet* tileSet);

private:
	MainGame* _mainGame;
	ResourceLocator* _resourceLocator;
	LevelMap* _levelMap;

	std::map<std::string, Level> _loadedLevels;
};


#endif //LOADED_LEVEL_CACHE_H
