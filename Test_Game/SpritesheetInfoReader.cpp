#include "SpritesheetInfoReader.h"

#include <fstream>
#include <iostream> 
#include <map>

namespace 
{
	void mapContains(const std::map<std::string, int>& map, const std::string& index, bool& fail)
	{
		if (map.find(index) == map.end())
		{
			std::cout << "Missing "<< index << std::endl; 
			fail = true;
		}
	};
}


SpritesheetInfoReader::SpritesheetInfoReader(const std::string& fullPath)
	:_fullPath(fullPath), _infoPath(fullPath.substr(0, fullPath.rfind('.')) + ".info")
{
}

SpritesheetInfo SpritesheetInfoReader::info()
{
	std::ifstream fileInfo(_infoPath);
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
	catch ( ... )
	{
		std::cout << "Failed to read '" << _infoPath << '\'' << std::endl; 
		return SpritesheetInfo(-1, -1, -1, -1, -1, -1); //dummy info
	}

	bool fail = false; //this is dumb 
	mapContains(loadedValues, "numSprites", fail);
	mapContains(loadedValues, "spriteWidth", fail);
	mapContains(loadedValues, "spriteHeight", fail);
	mapContains(loadedValues, "numRows", fail);
	mapContains(loadedValues, "numCols", fail);
	mapContains(loadedValues, "padding", fail);

	return fail ? SpritesheetInfo(-1, -1, -1, -1, -1, -1):	
					SpritesheetInfo(loadedValues["numSprites"], 
									loadedValues["spriteWidth"],
									loadedValues["spriteHeight"],
									loadedValues["numRows"], 
									loadedValues["numCols"],
									loadedValues["padding"]);
}