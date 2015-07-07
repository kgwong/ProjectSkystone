#ifndef LEVELENTITIES_H
#define LEVELENTITIES_H

#include <vector>
#include <list>

#include "Player.h"
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
	std::list<PlayerProjectile> playerProjectiles;
	/*maybe std::vector would be better, projectiles are not expected to last long,
	so the length of the vector would short, therefore random removals would not 
	take long either. vector also is more cache friendly*/
};

#endif //LEVELENTITIES_H