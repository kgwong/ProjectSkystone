#ifndef SPRITESHEET_INFO_H
#define SPRITESHEET_INFO_H

struct SpritesheetInfo
{
	SpritesheetInfo(int n, int w, int h, int r, int c, int p = 0)
		:num(n), width(w), height(h), perRow(r), perColumn(c), padding(p)
	{};
	int num;
	int width;
	int height;
	int perRow;
	int perColumn;
	int padding;
};

#endif //SPRITESHEET_INFO_H