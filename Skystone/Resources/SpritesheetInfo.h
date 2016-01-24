#ifndef SPRITESHEET_INFO_H
#define SPRITESHEET_INFO_H

#include <vector>

struct SpriteSheetInfo
{
	int num;
	int width;
	int height;
	int numRows;
	int numCols;
	int padding;

	std::vector<int> frameTimes;
};

#endif //SPRITESHEET_INFO_H