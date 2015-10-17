#ifndef BLOCK_H
#define BLOCK_H

#include "GameConstants.h"
#include "Point.h"

struct Block
{
	static Block getBlock(Point position)
	{
		return getBlock(position.x, position.y);
	};

	static Block getBlock(int x, int y)
	{
		return Block{ y / Constants::TILE_SIZE / Constants::TILES_PER_BLOCK_HEIGHT,
					  x / Constants::TILE_SIZE / Constants::TILES_PER_BLOCK_WIDTH };
	};

	Block operator+(const Block& b2)
	{
		return Block{ this->r + b2.r , this->c + b2.c };
	}

	int r;
	int c;
};

#endif BLOCK_H