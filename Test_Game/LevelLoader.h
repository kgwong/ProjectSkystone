#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>

#include "TileArrangement.h"

class LevelLoader
{
public:
	static TileArrangement load(const std::string& filepathm, TileSet* tileSet); 
};

#endif //LEVEL_LOADER_H

