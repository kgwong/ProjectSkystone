#include "GameObjectBuilder.h"

#include <memory>

#include "GameConstants.h"
#include "Resources/Resources.h"

#include "Components/Render/SpriteRenderer.h"
#include "BasicEnemyMovementComponent.h"
#include "RandomJumperComponent.h"
#include "TrackerComponent.h"
#include "FallingAIComponent.h"
#include "HealthComponent.h"
#include "ColliderComponent.h"
#include "FlyingAIComponent.h"
#include "AIjump.h"
#include "PlayerAttackState.h"
#include "PlayerComponent.h"
#include "PlayerMovementState.h"
#include "LevelChangeComponent.h"
#include "PlayerControlComponent.h"


GameObjectBuilder::GameObjectBuilder()
{
}

GameObjectBuilder::~GameObjectBuilder()
{
}

void GameObjectBuilder::buildPlayer(GameObject& player)
{
	player.setType(GameObject::Type::PLAYER);
	player.addComponent(std::make_shared<SpriteRenderer>(player, Resources::getSpriteSheet("Images/run_cycle.png")));
	player.addComponent(std::make_shared<PhysicsComponent>(player));
	player.addComponent(std::make_shared<HealthComponent>(player, 100));
	player.addComponent(std::make_shared<ColliderComponent>(player));
	player.addComponent(std::make_shared<LevelChangeComponent>(player));
	player.addComponent(std::make_shared<PlayerComponent>(player));
	//player.addComponent(std::make_shared<PlayerMovementState>(player));
	//player.addComponent(std::make_shared<PlayerAttackState>(player));
	player.addComponent(std::make_shared<PlayerControlComponent>(player));
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

std::shared_ptr<GameObject> GameObjectBuilder::buildPlayerHook(ComponentSystem& componentSystem, const std::string& name)
{
	return playerHookBuilder_.build(componentSystem, name);
}