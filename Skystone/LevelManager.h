#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "LevelMap.h"
#include "LevelLoader.h"

class Player;

class LevelManager
{
public:
	LevelManager(TextureLoader* tl);
	~LevelManager();

	void setTextureLoader(TextureLoader* textureLoader);

	void setPlayer(Player* player);

	void initStartingLevel();

	LevelMap* getLevelMap();
	Level* getCurrentLevel();

	void setNextLevel(int levelID, Point newPlayerPosition);
	bool changeLevelIfNecessary();

private:
	TextureLoader* textureLoader_;
	Player* player_;

	LevelMap levelMap_;
	LevelLoader levelLoader_;
	Level* currLevel_;

	int nextLevelID_;
	Point newPlayerPosition_;

	bool levelWasChangedFlag_;

};

#endif //LEVEL_MANAGER_H
