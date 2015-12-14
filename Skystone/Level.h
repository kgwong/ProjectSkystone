#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"
#include "PlayerProjectile.h"
#include "TileArrangement.h"
#include "Pickup.h"

#include "ComponentSystem.h"

#include <iostream> //
#include <memory>

class Background;
class LevelLoader;
class LevelMap;
class LevelManager;
class TextureLoader;
class GameObjectBuilder;
class SpriteRenderer;

class Level
{

public:
	Level(int levelID);
	~Level();

	void onEnter();
	void onExit();

	void setLevelManager(LevelManager* levelManager);
	void setGameObjectBuilder(GameObjectBuilder* gameObjectBuilder);
	void setBackgroundFromSprite(std::shared_ptr<SpriteRenderer> spriteRenderer);

	void setPlayer(Player* player, Point startPosition);
	Point getPlayerPos();

	LevelManager* getLevelManager();
	void startEntityComponents();

	void update();
	void render(GameWindow& window);

	int getID();

	void setNextLevel(Direction dir);

	int getLevelWidth() const; //pixels
	int getLevelHeight() const;

	void addPlayerProjectileAtLocation(Point position, int vel, double degrees);
	void addPickupAtLocation(Point position);
	void addEnemyAtLocation(const std::string& name, Point position);
	void addTileAtLocation(int tileType, Point position);

public:
	Player* player;
	TileArrangement tileArrangement;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<PlayerProjectile>> playerProjectiles;
	std::vector<std::shared_ptr<Pickup>> pickups;

private:
	TextureLoader* textureLoader_;
	LevelManager* levelManager_;
	GameObjectBuilder* gameObjectBuilder_;
	std::shared_ptr<Background> background_;

	Block oldPlayerBlock_;
	Point oldPlayerPosInBlock_;
	int levelID_;

	ComponentSystem componentSystem_;

private:
	template <typename Entity>
	void startComponents(std::vector<std::shared_ptr<Entity>>& v);

	void updateBackground();
	void updateTiles();
	void updatePlayer();
	void updatePlayerProjectiles();	
	void updateEnemies();
	void updatePickups();

	template <typename Entity>
	void updateEntityVector(std::vector<std::shared_ptr<Entity>>& v); //isDead() and update() must be defined for Entity;
	
	void renderPlayer();

};

template <typename Entity>
void Level::startComponents(std::vector<std::shared_ptr<Entity>>& v)
{
	for (auto& entity : v)
		entity->callStartOnComponents(*this);
}

template <typename Entity>
void Level::updateEntityVector(std::vector<std::shared_ptr<Entity>>& v)
{
	auto it = v.begin();
	while (it != v.end())
	{
		auto& obj = *it;
		if (obj->alive())
		{
			obj->update(*this);
			++it;
		}
		else
		{
			obj->onDeath(*this);
			obj->clearComponents();
			it = v.erase(it);
		}
	}
}

#endif //LEVEL_H

