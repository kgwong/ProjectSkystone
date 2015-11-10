#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "LevelMap.h"
#include "LevelLoader.h"

class MainGame; // 
class Player;

class LevelManager
{
public:
	LevelManager(MainGame* mainGame, TextureLoader* tl, Player* player);
	~LevelManager();

	void setTextureLoader(TextureLoader* textureLoader);

	void setPlayer(Player* player);

	Level* getCurrentLevel();
	bool getlevelWasChangedFlag();
	void setLevelWasChangedFlag(bool flag);

	void setNextLevel(int levelID, Point newPlayerPosition);
	void changeLevel();

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
