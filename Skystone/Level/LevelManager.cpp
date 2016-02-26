#include "LevelManager.h"

#include "Level.h"

#include "Application/Log.h"

LevelManager::LevelManager()
	:player_(nullptr),
	levelMap_(10, 10),
	currLevel_(nullptr),
	nextLevelID_(INVALID_LEVEL_ID)
{
	levelMap_.addLevel(1, 2, 2, 1, 1);
	levelMap_.addLevel(2, 1, 2, 1, 3);
	levelMap_.addLevel(3, 2, 1, 0, 2);
	levelMap_.addLevel(4, 1, 1, 0, 4);

	levelLoader_.setLevelManager(this);
}

LevelManager::~LevelManager()
{
}

void LevelManager::setPlayer(GameObject* player)
{
	player_ = player;
}

void LevelManager::initStartingLevel()
{
	if (player_ != nullptr)
	{
		currLevel_ = levelLoader_.getLevelWithID(4);
		currLevel_->setPlayer(player_, Point{ currLevel_->getLevelWidth() / 2, currLevel_->getLevelHeight() / 2 });
		currLevel_->onEnter();
	}
	else
	{
		LOG("WARNING") << "set Player first";
	}
}

LevelMap* LevelManager::getLevelMap()
{
	return &levelMap_;
}

Level* LevelManager::getCurrentLevel()
{
	return currLevel_;
}


void LevelManager::setNextLevel(int levelID, Point newPlayerPosition)
{
	nextLevelID_ = levelID;
	newPlayerPosition_ = newPlayerPosition;
}

bool LevelManager::changeLevelIfNecessary()
{
	if (nextLevelID_ != INVALID_LEVEL_ID)
	{
		currLevel_->onExit();
		currLevel_ = levelLoader_.getLevelWithID(nextLevelID_);
		currLevel_->setPlayer(player_, newPlayerPosition_);
		currLevel_->onEnter();
		nextLevelID_ = INVALID_LEVEL_ID;
		return true;
	}
	return false;
}

