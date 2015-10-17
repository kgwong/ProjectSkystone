#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <vector>
#include <map>

#include "Direction.h"
#include "Block.h"

class Level;

class LevelMap
{
public:
	LevelMap(int rows, int cols);
	~LevelMap();

	void addLevel(int id, int blockWidth, int blockHeight, int row, int col);
	void addLevel(Level& level, int row, int col);
	
	Block getAdjBlock(Block block, Direction dir);
	int getLevelID(Block block, Direction dir);
	int getLevelID(Block block);

	Block getBaseBlock(Level& level);
	Block getBaseBlock(int levelID);

	void print();

private:
	std::vector<std::vector<int>> _levels;
	std::map<int, Block> _levelBasePosition;
	int _numRows, _numCols;
};

#endif //LEVEL_MAP_H

