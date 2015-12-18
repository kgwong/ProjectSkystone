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

	static void buildPlayer(TextureLoader* textureLoader, GameObject& player);

	GameObject& buildTile(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild);
	std::shared_ptr<GameObject> buildEnemy(ComponentSystem& componentSystem, const std::string& enemyName);
	std::shared_ptr<GameObject> buildItemDrop(ComponentSystem& componentSystem, const std::string& itemName);
	std::shared_ptr<GameObject> buildPlayerProjectile(ComponentSystem& componentSystem, const std::string& name);


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