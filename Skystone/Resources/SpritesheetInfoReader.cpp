#include "SpritesheetInfoReader.h"

#include <fstream>
#include <iostream> 
#include <map>

#include "Application/Log.h"

namespace 
{
	void mapContains(const std::map<std::string, int>& map, const std::string& index, bool& fail)
	{
		if (map.find(index) == map.end())
		{
			LOG("WARNING") << "Missing " << index;
			fail = true;
		}
	};
}


SpritesheetInfoReader::SpritesheetInfoReader(const std::string& fullPath)
	:_fullPath(fullPath), _infoPath(fullPath.substr(0, fullPath.rfind('.')) + ".info")
{
}

SpriteSheetInfo* SpritesheetInfoReader::info()
{
	std::ifstream fileInfo(_infoPath);
	if (!fileInfo)
		return nullptr;

	std::map<std::string, int> loadedValues;

	std::string parameterName;
	int parameterValue;

	try
	{
		for (int i = 0; i < 6; ++i)
		{
			fileInfo >> parameterName >> parameterValue;
			loadedValues.insert(std::make_pair(parameterName, parameterValue));
		}

		int frameTime;
		while (fileInfo >> frameTime)
		{
			info_.frameTimes.push_back(frameTime);
		}
	}
	catch (...)
	{
		LOG_STREAM(std::cerr) << "Failed to read '" << _infoPath << '\'';
		return nullptr;
	}

	bool fail = false; //this is dumb 
	mapContains(loadedValues, "numSprites", fail);
	mapContains(loadedValues, "spriteWidth", fail);
	mapContains(loadedValues, "spriteHeight", fail);
	mapContains(loadedValues, "numRows", fail);
	mapContains(loadedValues, "numCols", fail);
	mapContains(loadedValues, "padding", fail);

	if (fail)
		return nullptr;
	else
	{
		info_.num = loadedValues["numSprites"];
		info_.width = loadedValues["spriteWidth"];
		info_.height = loadedValues["spriteHeight"];
		info_.numRows = loadedValues["numRows"];
		info_.numCols = loadedValues["numCols"];
		info_.padding = loadedValues["padding"];

		return &info_;
	}

}