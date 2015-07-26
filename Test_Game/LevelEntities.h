#ifndef LEVELENTITIES_H
#define LEVELENTITIES_H

#include <vector>
#include <list>

#include "Tile.h"
#include "Enemy.h"
#include "PlayerProjectile.h"
#include "Pickup.h"

class Player;

struct LevelEntities 
{
	Player* player;
	std::vector<std::vector<Tile>> tiles;
	int tileSize;
	std::vector<Enemy> enemies;
	std::vector<PlayerProjectile> playerProjectiles;
	std::vector<Pickup> pickups;

};

#endif //LEVELENTITIES_H