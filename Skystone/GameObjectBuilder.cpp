#include "GameObjectBuilder.h"

#include "GameConstants.h"
#include "TextureLoader.h"

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

GameObject& GameObjectBuilder::buildTile(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild)
{
	return tileBuilder_.build(componentSystem, tileType, tileToBuild);
}

std::shared_ptr<GameObject> GameObjectBuilder::buildEnemy(ComponentSystem& componentSystem, const std::string& enemyName)
{
	return enemyBuilder_.build(componentSystem, enemyName);
}

std::shared_ptr<GameObject> GameObjectBuilder::buildItemDrop(ComponentSystem& componentSystem, const std::string& itemName)
{
	return itemDropBuilder_.build(componentSystem, itemName);
}

std::shared_ptr<GameObject> GameObjectBuilder::buildPlayerProjectile(ComponentSystem& componentSystem, const std::string& name)
{
	return playerProjectileBuilder_.build(componentSystem, name);
}

TextureSheet* GameObjectBuilder::getTexture(const std::string & path)
{
	return textureLoader_->getTextureSheet(path);
}
