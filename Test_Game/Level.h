#ifndef LEVEL_H
#define LEVEL_H

#include "GameWindow.h"
#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include "PlayerProjectile.h"
#include "TileSet.h"
#include "TileArrangement.h"
#include "Pickup.h"

#include "ResourceLocator.h"
#include "EnemyBuilder.h"

#include <map>

class MainGame;
class LevelLoader;

class Level
{
	friend LevelLoader;

public:
	Level(MainGame* mainGame, GameWindow* window, ResourceLocator* resourceLocator);
	~Level();

	void load(const std::string& filepath, TileSet* tileSet);
	void setPlayer(Player* player);

	void update();
	void render();

	int getID();

	int getBlockWidth();
	int getBlockHeight();

	int getLevelWidth() const;
	int getLevelHeight() const;

	void addPlayerProjectileAtLocation(Point position, int vel, Direction dir);
	void addPickupAtLocation(Point position);
	void addEnemyAtLocation(const std::string& name, Point position);

public:
	Player* player;
	TileArrangement tileArrangement;
	std::vector<Enemy> enemies;
	std::vector<PlayerProjectile> playerProjectiles;
	std::vector<Pickup> pickups;

private:
	MainGame* _mainGame;
	GameWindow* _window;
	ResourceLocator* _resourceLocator;
	EnemyBuilder _enemyBuilder;

	int _levelID;
	int _blockWidth, _blockHeight;

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
			it->onDeath(*this);
			it = v.erase(it);
		}
		else
		{
			it->update(*this);
			++it;
		}
	}
}

template <typename Entity>
void Level::renderEntityVector(std::vector<Entity>& v)
{
	for (auto& entity : v)
		entity.render();
}


#endif //LEVEL_H

