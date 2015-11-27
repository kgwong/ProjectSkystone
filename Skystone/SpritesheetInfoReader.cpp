#include "SpritesheetInfoReader.h"

#include <fstream>
#include <iostream> 
#include <map>

#include "Log.h"

namespace 
{
	void mapContains(const std::map<std::string, int>& map, const std::string& index, bool& fail)
	{
		if (map.find(index) == map.end())
		{
			LOG_COUT << "Missing " << index;
			fail = true;
		}
	};
}


SpritesheetInfoReader::SpritesheetInfoReader(const std::string& fullPath)
	:_fullPath(fullPath), _infoPath(fullPath.substr(0, fullPath.rfind('.')) + ".info")
{
}

SpritesheetInfo* SpritesheetInfoReader::info()
{
	std::ifstream fileInfo(_infoPath);
	if (!fileInfo)
		return nullptr;

	std::map<std::string, int> loadedValues;

	std::string parameterName;
	int parameterValue;

	try
	{
		while (fileInfo >> parameterName >> parameterValue)
		{
			loadedValues.insert(std::make_pair(parameterName, parameterValue));
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
		info_ =	SpritesheetInfo{ loadedValues["numSprites"],
				loadedValues["spriteWidth"],
				loadedValues["spriteHeight"],
				loadedValues["numRows"],
				loadedValues["numCols"],
				loadedValues["padding"] };

		return &info_;
	}

}