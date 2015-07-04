#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <vector>

#include "TileSet.h"
#include "Sprite.h"
#include "Tile.h"
#include "GameWindow.h"
#include "Enemy.h"

class Level
{
public:
	Level(GameWindow* window, TileSet* tileSet);
	~Level();

	void load(const std::string& filepath);
	void drawLevel();
	void drawEnemies();

	int getLevelWidth() const;
	int getLevelHeight() const;

	int getTileSize() const;


public:
	std::vector<std::vector<Tile>> tileArrangement;
	std::vector<Enemy> enemies;

private:
	Sprite enemySprite;
	GameWindow* _window;
	TileSet* _tileSet;

	int _tileSize;

	int _numTilesWide;
	int _numTilesHigh;
};

#endif //LEVEL_H

