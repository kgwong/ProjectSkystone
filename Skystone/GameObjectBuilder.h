#ifndef GAME_OBJECT_BUILDER_H
#define GAME_OBJECT_BUILDER_H

#include "EnemyBuilder.h"
#include "TileBuilder.h"
#include "ItemDropBuilder.h"
#include "PlayerProjectileBuilder.h"

class TextureSheet;
class ComponentSystem;

class GameObjectBuilder
{
public:
	GameObjectBuilder(TextureLoader* textureLoader);
	~GameObjectBuilder();

	//test for possibility of RVO
	Tile& buildTile(ComponentSystem& componentSystem, int tileType, Tile& tileToBuild);
	Enemy& buildEnemy(ComponentSystem& componentSystem, const std::string& enemyName, Enemy& enemyToBuild);
	Pickup& buildItemDrop(ComponentSystem& componentSystem, const std::string& itemName, Pickup& itemDropToBuild);
	PlayerProjectile& buildPlayerProjectile(ComponentSystem& componentSystem, const std::string& name, PlayerProjectile& projectileToBuild);

	//temp
	TextureSheet* getTexture(const std::string& path);

private:
	TextureLoader* textureLoader_;
	EnemyBuilder enemyBuilder_;
	TileBuilder tileBuilder_;
	ItemDropBuilder itemDropBuilder_;
	PlayerProjectileBuilder playerProjectileBuilder_;
};

#endif GAME_OBJECT_BUILDER_H