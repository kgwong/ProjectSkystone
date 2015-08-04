#ifndef SPRITESHEET_INFO_H
#define SPRITESHEET_INFO_H

struct SpritesheetInfo
{
	SpritesheetInfo(int n, int w, int h, int r, int c, int p = 0)
		:num(n), width(w), height(h), numRows(r), numCols(c), padding(p)
	{};
	int num;
	int width;
	int height;
	int numRows;
	int numCols;
	int padding;
};

#endif //SPRITESHEET_INFO_H