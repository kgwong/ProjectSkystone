#ifndef LEVEL_MAP_LOADER
#define LEVEL_MAP_LOADER

#include "LevelMap.h"

class LevelMapLoader
{
public:
	static void load(LevelMap& levelmap, const std::string& filepath);
};

#endif //LEVEL_MAP_LOADER
