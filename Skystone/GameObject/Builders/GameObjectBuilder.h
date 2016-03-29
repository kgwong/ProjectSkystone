#ifndef GAME_OBJECT_BUILDER_H
#define GAME_OBJECT_BUILDER_H

#include "EnemyBuilder.h"
#include "TileBuilder.h"
#include "ItemDropBuilder.h"
#include "PlayerProjectileBuilder.h"
#include "BackgroundBuilder.h"
#include "PlayerHookBuilder.h"
#include "EnemyProjectileBuilder.h"

class ComponentSystem;

class GameObjectBuilder
{
public:
	GameObjectBuilder();
	~GameObjectBuilder();

	static void buildPlayer(GameObject& player);

	GameObject& buildTile(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild);
	std::shared_ptr<GameObject> buildEnemy(ComponentSystem& componentSystem, const std::string& enemyName);
	std::shared_ptr<GameObject> buildItemDrop(ComponentSystem& componentSystem, const std::string& itemName);
	std::shared_ptr<GameObject> buildPlayerProjectile(ComponentSystem& componentSystem, const std::string& name);
	std::shared_ptr<GameObject> buildBackground(ComponentSystem& componentSystem, const std::string backgroundName);
	std::shared_ptr<GameObject> buildEnemyProjectile(ComponentSystem& componentSystem, const std::string& name);
	//the hooks
	std::shared_ptr<GameObject> buildPlayerHook(ComponentSystem& componentSystem, const std::string& name);
	

private:
	EnemyBuilder enemyBuilder_;
	TileBuilder tileBuilder_;
	ItemDropBuilder itemDropBuilder_;
	PlayerProjectileBuilder playerProjectileBuilder_;
	BackgroundBuilder backgroundBuilder_;
	/////////////////////////////////////////////////
	PlayerHookBuilder playerHookBuilder_;
	EnemyProjectileBuilder enemyProjectileBuilder_;
};

#endif GAME_OBJECT_BUILDER_H