#include "GameObjectBuilder.h"

#include "GameConstants.h"
#include "TextureLoader.h"
#include "Enemy.h"
#include "Tile.h"

#include "SpriteRenderer.h"
#include "BasicEnemyMovementComponent.h"
#include "RandomJumperComponent.h"
#include "TrackerComponent.h"
#include "FallingAIComponent.h"
#include "HealthComponent.h"
#include "ColliderComponent.h"
#include "FlyingAIComponent.h"
#include "AIjump.h"


GameObjectBuilder::GameObjectBuilder(TextureLoader* textureLoader)
	:enemyBuilder_(textureLoader), 
	tileBuilder_(textureLoader),
	itemDropBuilder_(textureLoader),
	playerProjectileBuilder_(textureLoader)
{
}

GameObjectBuilder::~GameObjectBuilder()
{
}

Tile& GameObjectBuilder::buildTile(int tileType, Tile& tileToBuild)
{
	return tileBuilder_.build(tileType, tileToBuild);
}

Enemy& GameObjectBuilder::buildEnemy(const std::string& enemyName, Enemy& enemyToBuild)
{
	return enemyBuilder_.build(enemyName, enemyToBuild);
}

Pickup& GameObjectBuilder::buildItemDrop(const std::string& itemName, Pickup& itemDropToBuild)
{
	return itemDropBuilder_.build(itemName, itemDropToBuild);
}

PlayerProjectile& GameObjectBuilder::buildPlayerProjectile(const std::string& name, PlayerProjectile& projectileToBuild)
{
	return playerProjectileBuilder_.build(name, projectileToBuild);
}
