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
	:textureLoader_(textureLoader),
	enemyBuilder_(textureLoader), 
	tileBuilder_(textureLoader),
	itemDropBuilder_(textureLoader),
	playerProjectileBuilder_(textureLoader)
{
}

GameObjectBuilder::~GameObjectBuilder()
{
}

Tile& GameObjectBuilder::buildTile(ComponentSystem& componentSystem, int tileType, Tile& tileToBuild)
{
	return tileBuilder_.build(componentSystem, tileType, tileToBuild);
}

Enemy& GameObjectBuilder::buildEnemy(ComponentSystem& componentSystem, const std::string& enemyName, Enemy& enemyToBuild)
{
	return enemyBuilder_.build(componentSystem, enemyName, enemyToBuild);
}

Pickup& GameObjectBuilder::buildItemDrop(ComponentSystem& componentSystem, const std::string& itemName, Pickup& itemDropToBuild)
{
	return itemDropBuilder_.build(componentSystem, itemName, itemDropToBuild);
}

PlayerProjectile& GameObjectBuilder::buildPlayerProjectile(ComponentSystem& componentSystem, const std::string& name, PlayerProjectile& projectileToBuild)
{
	return playerProjectileBuilder_.build(componentSystem, name, projectileToBuild);
}

TextureSheet* GameObjectBuilder::getTexture(const std::string & path)
{
	return textureLoader_->getTextureSheet(path);
}
