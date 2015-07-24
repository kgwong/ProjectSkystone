#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>

#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include "PlayerProjectile.h"
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
	void render();

	int getLevelWidth() const;
	int getLevelHeight() const;

	int getTileSize() const;

private:
	LevelEntities _entities;

	Sprite enemySprite;
	GameWindow* _window;
	TileSet* _tileSet;

	int _tileSize;

	int _numTilesWide;
	int _numTilesHigh;

private:
	void updateTiles();
	void updatePlayer();
	void updatePlayerProjectiles();
	void updateEnemies();

	void renderPlayer();
	void renderTiles();
	void renderEnemies();
	void renderPlayerProjectiles();
};

#endif //LEVEL_H

