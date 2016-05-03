#include "GameObjectBuilder.h"

#include <memory>

#include "Game/GameConstants.h"

#include "Components/Render/SpriteRenderer.h"
#include "Components/Render/ColliderBoxRenderer.h"
#include "Components/Common/HealthComponent.h"
#include "Components/Player/Attack/PlayerAttackState.h"
#include "Components/Player/PlayerComponent.h"
#include "Components/Player/Movement/PlayerMovementState.h"
#include "Components/Player/LevelChangeComponent.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/GUI/HealthBar.h"

GameObjectBuilder::GameObjectBuilder()
{
}

GameObjectBuilder::~GameObjectBuilder()
{
}

void GameObjectBuilder::buildPlayer(GameObject& player)
{
	player.setType(GameObject::Type::PLAYER);
	player.addComponent(std::make_shared<SpriteRenderer>(player, "Images/run_cycle.png"));
	//player.addComponent(std::make_shared<ColliderBoxRenderer>(player));
	player.addComponent(std::make_shared<PhysicsComponent>(player));
	player.addComponent(std::make_shared<HealthComponent>(player, 100));
	player.addComponent(std::make_shared<ColliderComponent>(player));
	player.addComponent(std::make_shared<LevelChangeComponent>(player));
	player.addComponent(std::make_shared<PlayerComponent>(player));
	//player.addComponent(std::make_shared<PlayerMovementState>(player));
	//player.addComponent(std::make_shared<PlayerAttackState>(player));
	player.addComponent(std::make_shared<PlayerControlComponent>(player));
	player.addComponent(std::make_shared<HealthBar>(player));
	//player.addComponent(std::make_shared<HookComponent>(player));
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

std::shared_ptr<GameObject> GameObjectBuilder::buildBackground(ComponentSystem& componentSystem, const std::string backgroundName)
{
	return backgroundBuilder_.build(componentSystem, backgroundName);
}

std::shared_ptr<GameObject> GameObjectBuilder::buildScrollingBackground(ComponentSystem& componentSystem, const std::string backgroundName)
{
	return scrollingBackgroundBuilder_.build(componentSystem, backgroundName);
}

std::shared_ptr<GameObject> GameObjectBuilder::buildGUI(ComponentSystem& componentSystem, const std::string& name, GameObject* player)
{
	return guiBuilder_.build(componentSystem, name, player);
}

std::shared_ptr<GameObject> GameObjectBuilder::buildEnemyProjectile(ComponentSystem& componentSystem, const std::string& name)
{
	return enemyProjectileBuilder_.build(componentSystem, name);
}

std::shared_ptr<GameObject> GameObjectBuilder::buildPlayerHook(ComponentSystem& componentSystem, const std::string& name)
{
	return playerHookBuilder_.build(componentSystem, name);
}