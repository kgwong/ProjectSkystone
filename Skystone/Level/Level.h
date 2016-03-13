#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

#include <SDL/SDL.h>

#include "GameObject/GameObjectContainer.h"
#include "Block.h"
#include "GameTypes/Direction.h"
#include "ComponentSystem/ComponentSystem.h"

class LevelLoader;
class LevelMap;
class LevelManager;
class SpriteRenderer;
class SpriteSheet;

class Level
{
private:
	static GameObjectBuilder gameObjectBuilder_;

public:
	Level(int levelID);
	~Level();

	void onEnter();
	void onExit();

	void setLevelManager(LevelManager* levelManager);
	void setBackgroundLayerFromSprite(SpriteSheet* backgroundSprite, int layer, bool scrollx, bool scrolly);

	void setPlayer(GameObject* player, Point startPosition);
	Point getPlayerPos();

	LevelManager* getLevelManager();

	void handleInput(SDL_Event& e);
	void update();
	void render(GameWindow& window, float percBehind);

	int getID();

	void setNextLevel(Direction dir);

	int getLevelWidth(); //pixels
	int getLevelHeight();

	void addPlayerHookAtLocation(Point position, int velocity, double degrees);

public:
	GameObjectContainer gameObjects;

	//there should only be one hook per cast.
	std::shared_ptr<GameObject> playerHook;
	//int numHook_;

private:
	LevelManager* levelManager_;
	std::shared_ptr<GameObject> background_;

	Block oldPlayerBlock_;
	Point oldPlayerPosInBlock_;
	int levelID_;

	ComponentSystem componentSystem_;

private:
	void updatePlayer();
};

#endif //LEVEL_H

