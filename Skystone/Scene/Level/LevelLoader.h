#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>
#include <map>
#include <memory>

#include "Level.h"

class LevelManager;

class LevelLoader
{
public:
	static const std::string LEVEL_FILEPATH_PREFIX;

public:
	LevelLoader();
	~LevelLoader();

	void setLevelManager(LevelManager* levelManager);
	
	Level* getLevelWithID(int levelID);

private:
	LevelManager* levelManager_;

	std::map<int, std::shared_ptr<Level>> loadedLevels_;

private:
	bool levelLoaded(int levelID);
	void load(const int levelID);

	std::string generateFilePath(const std::string& tag, int levelID);

	void loadEnemies(const std::string& filepath, Level* level);
	void loadTiles(const std::string& filepath, Level* level);
	void loadBackground(const std::string& filepath, Level* level);
};

#endif //LEVEL_LOADER_H

