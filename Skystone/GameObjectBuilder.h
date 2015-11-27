#ifndef GAME_OBJECT_BUILDER_H
#define GAME_OBJECT_BUILDER_H

#include "EnemyBuilder.h"
#include "TileBuilder.h"
#include "ItemDropBuilder.h"
#include "PlayerProjectileBuilder.h"

class GameObjectBuilder
{
public:
	GameObjectBuilder(TextureLoader* textureLoader);
	~GameObjectBuilder();

	//test for possibility of RVO
	Tile& buildTile(int tileType, Tile& tileToBuild);
	Enemy& buildEnemy(const std::string& enemyName, Enemy& enemyToBuild);
	Pickup& buildItemDrop(const std::string& itemName, Pickup& itemDropToBuild);
	PlayerProjectile& buildPlayerProjectile(const std::string& name, PlayerProjectile& projectileToBuild);

private:
	EnemyBuilder enemyBuilder_;
	TileBuilder tileBuilder_;
	ItemDropBuilder itemDropBuilder_;
	PlayerProjectileBuilder playerProjectileBuilder_;
};

#endif GAME_OBJECT_BUILDER_H