#ifndef SPRITESHEET_READER_H
#define SPRITESHEET_READER_H

#include <string>

#include "SpritesheetInfo.h"

class SpritesheetInfoReader
{
public:
	SpritesheetInfoReader(const std::string& fullPath);

	SpritesheetInfo* info();

private:
	std::string _fullPath;
	std::string _infoPath;

	SpritesheetInfo info_;
};


#endif //SPRITESHEET_READER_H
