#include "LevelManager.h"

#include "Level.h"
#include "LevelMapLoader.h"
#include "Application/Log.h"
#include "Game/GameInputs.h"

LevelManager::LevelManager()
	:player_(nullptr),
	levelMap_(20, 36),
	currLevel_(nullptr),
	nextLevelID_(INVALID_LEVEL_ID)
{
	//LevelMapLoader::load(levelMap_, "LevelMaps/test.txt");
	
	levelMap_.addLevel(0, 1, 6, 1, 1);
	levelMap_.addLevel(1, 4, 2, 5, 2);
	levelMap_.addLevel(2, 4, 2, 5, 6);
	levelMap_.addLevel(3, 2, 2, 5, 10);
	levelMap_.addLevel(4, 3, 2, 5, 12);
	levelMap_.addLevel(5, 3, 2, 5, 15);
	levelMap_.addLevel(6, 2, 2, 5, 18);
	levelMap_.addLevel(7, 2, 2, 5, 20);
	levelMap_.addLevel(8, 2, 2, 5, 22);
	levelMap_.addLevel(9, 3, 2, 5, 24);
	levelMap_.addLevel(10, 6, 6, 1, 27);

	levelLoader_.setLevelManager(this);
}

LevelManager::~LevelManager()
{
}

GameObject* LevelManager::getCameraFollowObject()
{
	return currLevel_->getCameraFollowObject();
}

void LevelManager::setPlayer(GameObject* player)
{
	Scene::setPlayer(player);
	player_ = player;
}

void LevelManager::setPlayer(GameObject* player, const Point& startPos)
{
	Scene::setPlayer(player, startPos);
	player_ = player;
}

void LevelManager::onEnter()
{
	if (currLevel_ == nullptr)
		initStartingLevel();
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
		currLevel_->setLevelManager(this);
		currLevel_->setSceneManager(sceneManager_); //
		currLevel_->setPlayer(player_, newPlayerPosition_);
		currLevel_->onEnter();
		nextLevelID_ = INVALID_LEVEL_ID;
		return true;
	}
	return false;
}

void LevelManager::handleInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
	{
		levelMap_.print();
	}

	if (GameInputs::keyDown(e, ControlType::ESC))
		setNextScene(SceneID::PAUSE);
	else
		currLevel_->handleInput(e);
}

void LevelManager::update()
{
	currLevel_->update();
	changeLevelIfNecessary();
}

void LevelManager::render(GameWindow& window, float percBehind)
{
	currLevel_->render(window, percBehind);
}

int LevelManager::getWidth()
{
	return currLevel_->getWidth();
}

int LevelManager::getHeight()
{
	return currLevel_->getHeight();
}

void LevelManager::initStartingLevel()
{
	if (player_ != nullptr)
	{
		currLevel_ = levelLoader_.getLevelWithID(0);
		currLevel_->setSceneManager(sceneManager_); //
		currLevel_->setPlayer(player_, Point{ currLevel_->getWidth() / 2, currLevel_->getHeight() / 2 });
		currLevel_->onEnter();
	}
	else
	{
		LOG("WARNING") << "set Player first";
	}
}

