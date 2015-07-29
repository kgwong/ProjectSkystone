#ifndef LEVELENTITIES_H
#define LEVELENTITIES_H

#include <vector>
#include <list>

#include "Tile.h"
#include "Enemy.h"
#include "PlayerProjectile.h"
#include "Pickup.h"

#include "ResourceLocator.h"

class Player;

struct LevelEntities 
{
	GameWindow* window;
	ResourceLocator* resourceLocator;
	Player* player;
	std::vector<std::vector<Tile>> tiles;
	int tileSize;
	std::vector<Enemy> enemies;
	std::vector<PlayerProjectile> playerProjectiles;
	std::vector<Pickup> pickups;

	void addPlayerProjectileAtLocation(Point position, int vel, Direction dir)
	{
		playerProjectiles.push_back( PlayerProjectile(position, vel, resourceLocator->getAnimation("Assets/Animations/playerProjectile.png"), dir) );
	};

	void addPickupAtLocation(Point position)
	{
		pickups.push_back(Pickup(window, resourceLocator->getSprite("Assets/Pickups/pickup.png")));
		pickups.back().setPos(position);
	};
};

#endif //LEVELENTITIES_H