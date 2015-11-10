#include "LevelManager.h"

#include "Level.h"

LevelManager::LevelManager(MainGame* mainGame, TextureLoader* tl, Player* player)
	:textureLoader_(tl),
	player_(player),
	levelMap_(10, 10),
	levelLoader_(mainGame, textureLoader_, &levelMap_),
	currLevel_(nullptr),
	nextLevelID_(-1),
	levelWasChangedFlag_(true)
{
	levelMap_.addLevel(1, 2, 2, 1, 1);
	levelMap_.addLevel(2, 1, 2, 1, 3);
	levelMap_.addLevel(3, 2, 1, 0, 2);
	levelMap_.addLevel(4, 1, 1, 0, 4);

	levelLoader_.setLevelManager(this);

	currLevel_ = &levelLoader_.getLevel("Levels/LevelTest4",
		textureLoader_->getTextureSheet("Assets/TileSets/bw.png"));
	currLevel_->setPlayer(player, Point{ currLevel_->getLevelWidth() / 2, currLevel_->getLevelHeight() / 2 });
	currLevel_->startEntityComponents();

}

LevelManager::~LevelManager()
{
}

void LevelManager::setTextureLoader(TextureLoader* textureLoader)
{
	textureLoader_ = textureLoader;
}

void LevelManager::setPlayer(Player* player)
{
	player_ = player;
}

Level* LevelManager::getCurrentLevel()
{
	return currLevel_;
}

bool LevelManager::getlevelWasChangedFlag()
{
	return levelWasChangedFlag_;
}

void LevelManager::setLevelWasChangedFlag(bool flag)
{
	levelWasChangedFlag_ = flag;
}

void LevelManager::setNextLevel(int levelID, Point newPlayerPosition)
{
	nextLevelID_ = levelID;
	newPlayerPosition_ = newPlayerPosition;
}

void LevelManager::changeLevel()
{
	if (nextLevelID_ != -1)
	{
		if (nextLevelID_ == 1)
		{
			currLevel_ = &levelLoader_.getLevel("Levels/LevelTest",
				textureLoader_->getTextureSheet("Assets/TileSets/bw.png"));
		}
		else if (nextLevelID_ == 2)
		{
			currLevel_ = &levelLoader_.getLevel("Levels/LevelTest2",
				textureLoader_->getTextureSheet("Assets/TileSets/bw.png"));
		}
		else if (nextLevelID_ == 3)
		{
			currLevel_ = &levelLoader_.getLevel("Levels/LevelTest3",
				textureLoader_->getTextureSheet("Assets/TileSets/bw.png"));
		}
		else if (nextLevelID_ == 4)
		{
			currLevel_ = &levelLoader_.getLevel("Levels/LevelTest4",
				textureLoader_->getTextureSheet("Assets/TileSets/bw.png"));
		}
		currLevel_->setPlayer(player_, newPlayerPosition_);
		currLevel_->startEntityComponents();
		//_window.getCamera().setLevelBounds(_currLevel->getLevelWidth(), _currLevel->getLevelHeight());
		levelWasChangedFlag_ = true;
		nextLevelID_ = -1;
	}
}

