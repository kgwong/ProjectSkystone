#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <vector>
#include <forward_list>
#include <list>

#include "TileSet.h"
#include "Sprite.h"
#include "GameWindow.h"
#include "LevelEntities.h"

class Level
{
public:
	Level(GameWindow* window, TileSet* tileSet);
	~Level();

	void load(const std::string& filepath);
	void setPlayer(Player* player);

	void update();
	void updatePlayer();
	void updatePlayerProjectiles();
	void updateEnemies();

	void render();
	void renderPlayer();
	void renderTiles();
	void renderEnemies();
	void renderPlayerProjectiles();

	int getLevelWidth() const;
	int getLevelHeight() const;

	int getTileSize() const;


public:
	LevelEntities _entities;

private:
	Sprite enemySprite;
	GameWindow* _window;
	TileSet* _tileSet;



	int _tileSize;

	int _numTilesWide;
	int _numTilesHigh;
};

#endif //LEVEL_H

