#include "LoadedLevelCache.h"



LoadedLevelCache::LoadedLevelCache(MainGame* mainGame,
	ResourceLocator* resourceLocator,
	LevelMap* levelMap)
	:_mainGame(mainGame),
	_resourceLocator(resourceLocator),
	_levelMap(levelMap)
{
}


LoadedLevelCache::~LoadedLevelCache()
{
}

Level& LoadedLevelCache::getLevel(const std::string& filepath, TileSet* tileSet)
{
	if (_loadedLevels.count(filepath) == 0)
	{
		_loadedLevels.insert(std::make_pair(filepath, Level(_mainGame, _resourceLocator, _levelMap)));
		_loadedLevels.at(filepath).load(filepath, tileSet);
	}
	return _loadedLevels.at(filepath);
}