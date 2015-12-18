#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "LevelMap.h"
#include "LevelLoader.h"

class Player;

class LevelManager
{
public:
	static const int INVALID_LEVEL_ID = -1;

public:
	LevelManager(TextureLoader* tl);
	~LevelManager();

	void setTextureLoader(TextureLoader* textureLoader);

	void setPlayer(GameObject* player);

	void initStartingLevel();

	LevelMap* getLevelMap();
	Level* getCurrentLevel();

	void setNextLevel(int levelID, Point newPlayerPosition);
	bool changeLevelIfNecessary();

private:
	TextureLoader* textureLoader_;
	GameObject* player_;

	LevelMap levelMap_;
	LevelLoader levelLoader_;
	Level* currLevel_;

	int nextLevelID_;
	Point newPlayerPosition_;

};

#endif //LEVEL_MANAGER_H
