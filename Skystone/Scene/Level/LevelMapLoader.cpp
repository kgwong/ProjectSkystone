#include "LevelMapLoader.h"

#include "Application/Log.h"
#include "Application/Path.h"

#include <fstream>

void LevelMapLoader::load(LevelMap& levelmap, const std::string& filepath)
{
	std::ifstream ifs(Path::getFullPath(filepath));
	if (!ifs)
	{
		LOG("ERROR") << "Failed to read from: " << filepath;
		return;
	}

	int numRows, numCols;
	ifs >> numRows >> numCols;
	levelmap.setSize(numRows, numCols);
	
	int levelID, width, height, row, col;
	while (ifs >> levelID >> width >> height >> row >> col)
	{
		levelmap.addLevel(levelID, width, height, row, col);
	}
}
