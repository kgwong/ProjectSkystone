#ifndef LEVELENTITIES_H
#define LEVELENTITIES_H

#include <vector>
#include <list>

//#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include "PlayerProjectile.h"

class Player;
class Tile;
class Enemy;
class PlayerProjectile;

struct LevelEntities 
{
	Player* player;
	std::vector<std::vector<Tile>> tiles;
	int tileSize;
	std::vector<Enemy> enemies;
	std::vector<PlayerProjectile> playerProjectiles;
};

#endif //LEVELENTITIES_H