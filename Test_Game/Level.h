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

class Level
{
public:
	Level(GameWindow* window, TileSet* tileSet, ResourceLocator* resourceLocator);
	~Level();

	void load(const std::string& filepath);
	void setPlayer(Player* player);

	void update();
	void render();

	int getLevelWidth() const;
	int getLevelHeight() const;

	void addPlayerProjectileAtLocation(Point position, int vel, Direction dir);
	void addPickupAtLocation(Point position);
	void addEnemyAtLocation(Point position);

public:
	Player* player;
	TileArrangement tileArrangement;
	std::vector<Enemy> enemies;
	std::vector<PlayerProjectile> playerProjectiles;
	std::vector<Pickup> pickups;

private:
	GameWindow* _window;
	ResourceLocator* _resourceLocator;
	TileSet* _tileSet;

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
	for (auto i = v.begin(); i != v.end(); ++i)
		i->render();
}


#endif //LEVEL_H

