#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "LevelMap.h"
#include "LevelLoader.h"

#include "Scene/Scene.h"

class LevelManager : public Scene
{
public:
	static const int INVALID_LEVEL_ID = -1;

public:
	LevelManager();
	~LevelManager();

	virtual GameObject* getCameraFollowObject();
	virtual void setPlayer(GameObject* player);
	virtual void setPlayer(GameObject* player, const Point& startPos);
	virtual void onEnter();

	LevelMap* getLevelMap();
	Level* getCurrentLevel();

	void setNextLevel(int levelID, Point newPlayerPosition);
	bool changeLevelIfNecessary();

	virtual void handleInput(SDL_Event& e);
	virtual void update();
	virtual void render(GameWindow& window, float percBehind);

	virtual int getWidth();
	virtual int getHeight();

private:
	GameObject* player_;

	LevelMap levelMap_;
	LevelLoader levelLoader_;
	Level* currLevel_;

	int nextLevelID_;
	Point newPlayerPosition_;

private:
	void initStartingLevel();
};

#endif //LEVEL_MANAGER_H
