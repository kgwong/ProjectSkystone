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

class Level : public Scene
{
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

private:
	LevelManager* levelManager_;

	Block oldPlayerBlock_;
	Point oldPlayerPosInBlock_;
	int levelID_;

private:
	void updatePlayer();
};

#endif //LEVEL_H

