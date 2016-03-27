#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

#include <SDL/SDL.h>

#include "Scene/Scene.h"
#include "Block.h"
#include "GameTypes/Direction.h"

class LevelLoader;
class LevelMap;
class LevelManager;
class SpriteRenderer;
class SpriteSheet;

class Level : public Scene
{
private:
	static GameObjectBuilder gameObjectBuilder_;

public:
	Level(int levelID);
	~Level();

	virtual GameObject* getCameraFollowObject();

	virtual void onEnter();
	virtual void onExit();

	void setLevelManager(LevelManager* levelManager);

	LevelManager* getLevelManager();

	virtual void update();

	int getID();

	void setNextLevel(Direction dir);

	virtual int getWidth(); 
	virtual int getHeight();

	//void addPlayerHookAtLocation(Point position, int velocity, double degrees);

public:
	//there should only be one hook per cast.
	//std::shared_ptr<GameObject> playerHook;
	//int numHook_;

private:
	LevelManager* levelManager_;
	std::shared_ptr<GameObject> background_;

	Block oldPlayerBlock_;
	Point oldPlayerPosInBlock_;
	int levelID_;

private:
	void updatePlayer();
};

#endif //LEVEL_H

