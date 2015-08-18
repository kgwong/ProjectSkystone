#include "LevelMap.h"

#include "Level.h"

LevelMap::LevelMap(int rows, int cols)
	:_levels(rows, std::vector<int>(cols, 0)),
	_numRows(rows),
	_numCols(cols)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::addLevel(int id, int blockWidth, int blockHeight, int row, int col)
{
	_levelBasePosition[id] = Block{ row, col };
	for (int r = row; r < row + blockWidth; ++r)
		for (int c = col; c < col + blockHeight; ++c)
			_levels[r][c] = id;
}

void LevelMap::addLevel(Level& level, int row, int col)
{
	int id = level.getID();
	_levelBasePosition[id] = Block{ row, col };
	for (int r = row; r < row + level.getBlockHeight(); ++r)
		for (int c = col; c < col + level.getBlockWidth(); ++c)
			_levels[r][c] = id;
}

Block LevelMap::getAdjBlock(Block block, Direction dir)
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

int LevelMap::getLevelID(Block block, Direction dir)
{
	return getLevelID(getAdjBlock(block, dir));
}

int LevelMap::getLevelID(Block block)
{
	return _levels[block.r][block.c];
}

Block LevelMap::getBaseBlock(Level& level)
{
	return getBaseBlock(level.getID());
}

Block LevelMap::getBaseBlock(int levelID)
{
	return _levelBasePosition[levelID];
}

void LevelMap::print()
{
	for (auto &v : _levels)
	{
		for (int i : v) std::cout << i << ' ';
		std::cout << std::endl;
	}
}
