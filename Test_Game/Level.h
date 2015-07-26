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

	Sprite enemySprite; //
	Sprite pickupSprite; //
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
	void updatePickups();

	template <typename Entity>
	void updateEntityVector(std::vector<Entity>& v); //isDead() and update() must be defined for Entity

	void renderPlayer();
	void renderTiles();
	void renderEnemies();
	void renderPlayerProjectiles();
	void renderPickups();

	template <typename Entity>
	void renderEntityVector(std::vector<Entity>& v); //render() must be defined for Entity
};

template <typename Entity>
void Level::updateEntityVector(std::vector<Entity>& v)
{
	auto it = v.begin();
	while (it != v.end())
	{
		if (it->isDead())
		{
			it->onDeath(_entities);
			it = v.erase(it);
		}
		else
		{
			it->update(_entities);
			++it;
		}
	}
}

template <typename Entity>
void Level::renderEntityVector(std::vector<Entity>& v)
{
	for (auto i = v.begin(); i != v.end(); ++i)
		i->render();
}


#endif //LEVEL_H

