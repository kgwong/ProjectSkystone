#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include "PlayerProjectile.h"
#include "TileArrangement.h"
#include "Pickup.h"

#include "TextureLoader.h"
#include "EnemyBuilder.h"
#include "TileBuilder.h"

class LevelLoader;
class LevelMap;
class TextureSheet;
class TileCreator;
class LevelManager;

class Level
{
	friend LevelLoader;

public:
	Level(TextureLoader* textureLoader);
	~Level();

	void setLevelManager(LevelManager* levelManager);
	void setTileCreator(TileCreator* tileCreator);
	void setEnemyBuilder(EnemyBuilder* enemyBuilder);
	void setTileBuilder(TileBuilder* tileBuilder);

	void load(const std::string& filepath, TextureSheet* tileSet, TileCreator* creator);
	void setPlayer(Player* player, Point newPlayerPosition);
	Point getPlayerPos();

	void startEntityComponents();

	void update();
	void render();

	int getID();

	void setNextLevel(Block oldBlock, Point oldPlayerPosition, Direction dir);

	int getBlockWidth();
	int getBlockHeight();

	int getLevelWidth() const; //pixels
	int getLevelHeight() const;

	void addPlayerProjectileAtLocation(Point position, int vel, double degrees);
	void addPickupAtLocation(Point position);
	void addEnemyAtLocation(const std::string& name, Point position);
	void addTileAtLocation(int tileType, Point position);

public:
	Player* player;
	TileArrangement tileArrangement;
	std::vector<Enemy> enemies;
	std::vector<PlayerProjectile> playerProjectiles;
	std::vector<Pickup> pickups;

private:
	TextureLoader* textureLoader_;
	LevelManager* levelManager_;
	EnemyBuilder* enemyBuilder_;
	TileCreator* tileCreator_;

	TileBuilder* tileBuilder_;

	int _levelID;
	int _blockWidth, _blockHeight;

private:
	template <typename Entity>
	void startComponents(std::vector<Entity>& v);

	void updateTiles();
	void updatePlayer();
	void updatePlayerProjectiles();
	void updateEnemies();
	void updatePickups();

	template <typename Entity>
	void updateEntityVector(std::vector<Entity>& v); //isDead() and update() must be defined for Entity

	void renderPlayer();
	void renderTiles();
	void renderEnemies();
	void renderPlayerProjectiles();
	void renderPickups();

	template <typename Entity>
	void renderEntityVector(std::vector<Entity>& v); //render() must be defined for Entity
};

template <typename Entity>
void Level::startComponents(std::vector<Entity>& v)
{
	for (auto& entity : v)
		entity.callStartOnComponents(*this);
}

template <typename Entity>
void Level::updateEntityVector(std::vector<Entity>& v)
{
	auto it = v.begin();
	while (it != v.end())
	{
		if (it->isDead())
		{
			it->onDeath(*this);
			it = v.erase(it);
		}
		else
		{
			it->update(*this);
			++it;
		}
	}
}

template <typename Entity>
void Level::renderEntityVector(std::vector<Entity>& v)
{
	for (auto& entity : v)
		entity.render(*this);
}

#endif //LEVEL_H

