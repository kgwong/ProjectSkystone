#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject/GameObject.h"
#include "Block.h"
#include "Direction.h"
#include "GameObject/TileArrangement.h"
#include "ComponentSystem/ComponentSystem.h"
#include "SDL/SDL.h"

#include <iostream> //
#include <memory>

class LevelLoader;
class LevelMap;
class LevelManager;
class GameObjectBuilder;
class SpriteRenderer;
class SpriteSheet;

class Level
{
public:
	Level(int levelID);
	~Level();

	void onEnter();
	void onExit();

	void setLevelManager(LevelManager* levelManager);
	void setGameObjectBuilder(GameObjectBuilder* gameObjectBuilder);
	void setBackgroundLayerFromSprite(SpriteSheet* backgroundSprite, int layer, bool scrollx, bool scrolly);

	void setPlayer(GameObject* player, Point startPosition);
	Point getPlayerPos();

	LevelManager* getLevelManager();
	void startEntityComponents();

	void handleInput(SDL_Event& e);
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

	void addPlayerHookAtLocation(Point position, int velocity, double degrees);

public:
	GameObject* player;
	TileArrangement tileArrangement;
	std::vector<std::shared_ptr<GameObject>> enemies;
	std::vector<std::shared_ptr<GameObject>> playerProjectiles;
	std::vector<std::shared_ptr<GameObject>> drops;

	//there should only be one hook per cast.
	std::shared_ptr<GameObject> playerHook;
	//int numHook_;

private:
	LevelManager* levelManager_;
	GameObjectBuilder* gameObjectBuilder_;
	std::shared_ptr<GameObject> background_;

	Block oldPlayerBlock_;
	Point oldPlayerPosInBlock_;
	int levelID_;

	ComponentSystem componentSystem_;
	//AudioPlayer audio_;

private:
	void startComponents(std::vector<std::shared_ptr<GameObject>>& v);
	void removeDeadObjects(std::vector<std::shared_ptr<GameObject>>& v);

	void updatePlayer();
};

#endif //LEVEL_H

