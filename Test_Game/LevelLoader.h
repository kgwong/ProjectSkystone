#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>

#include "TileSet.h"

class Level;

class LevelLoader
{
public:
	static void loadTiles(const std::string& filepath, Level& level, TileSet* tileSet); 
	static void loadEnemies(const std::string& filepath, Level& level);
};

#endif //LEVEL_LOADER_H

