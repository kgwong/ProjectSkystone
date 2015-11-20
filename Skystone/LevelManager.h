#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "LevelMap.h"
#include "LevelLoader.h"
#include "Background.h"

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
	Background* getBackground();

	void setNextLevel(int levelID, Point newPlayerPosition);
	bool changeLevelIfNecessary();

private:
	TextureLoader* textureLoader_;
	Player* player_;

	LevelMap levelMap_;
	LevelLoader levelLoader_;
	Level* currLevel_;
	Background background_;

	int nextLevelID_;
	Point newPlayerPosition_;

};

#endif //LEVEL_MANAGER_H
