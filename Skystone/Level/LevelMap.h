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
	
	Block getAdjBlock(Block block, Direction dir) const;
	int getLevelID(Block block, Direction dir) const;
	int getLevelID(Block block) const;

	Block getBaseBlock(Level& level) const;
	Block getBaseBlock(int levelID) const;

	void print();

private:
	std::vector<std::vector<int>> levels_;
	std::map<int, Block> levelBasePosition_;
	int numRows_, numCols_;
};

#endif //LEVEL_MAP_H

