#include "LevelMap.h"

#include "Level.h"
#include "LevelManager.h"
#include <iostream>
#include <iomanip>

LevelMap::LevelMap(int rows, int cols)
	:levels_(rows, std::vector<int>(cols, LevelManager::INVALID_LEVEL_ID)),
	numRows_(rows),
	numCols_(cols)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::addLevel(int id, int blockWidth, int blockHeight, int row, int col)
{
	levelBasePosition_[id] = Block{ row, col };
	for (int r = row; r < row + blockHeight; ++r)
		for (int c = col; c < col + blockWidth; ++c)
			levels_[r][c] = id;
}

Block LevelMap::getAdjBlock(Block block, Direction dir) const
{
	switch (dir)
	{
	case Direction::UP:
		block.r--;
		break;
	case Direction::DOWN:
		block.r++;
		break;
	case Direction::LEFT:
		block.c--;
		break;
	case Direction::RIGHT:
		block.c++;
		break;
	}
	return block;
}

int LevelMap::getLevelID(Block block, Direction dir) const
{
	return getLevelID(getAdjBlock(block, dir));
}

int LevelMap::getLevelID(Block block) const
{
	if (block.c < 0 || block.c >= numCols_ || block.r < 0 || block.r >= numRows_)
	{
		return LevelManager::INVALID_LEVEL_ID;
	}
	return levels_[block.r][block.c];
}

Block LevelMap::getBaseBlock(Level& level) const
{
	return getBaseBlock(level.getID());
}

Block LevelMap::getBaseBlock(int levelID) const
{
	if (levelID == LevelManager::INVALID_LEVEL_ID)
	{
		return Block();
	}
	return levelBasePosition_.at(levelID);
}

void LevelMap::print()
{
	for (auto &v : levels_)
	{
		for (int i : v) 
			std::cout << std::setw(2) << i << ' ';
		std::cout << std::endl;
	}
}
