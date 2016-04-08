#include "SceneManager.h"



SceneManager::SceneManager()
	:nextSceneID_(SceneID::INVALID)
{
}


SceneManager::~SceneManager()
{
}

GameObject* SceneManager::getCameraFollowObject()
{
	return currentScene_->getCameraFollowObject();
}

void SceneManager::setPlayer(GameObject* player)
{
	player_ = player;
	initLevels(player);
	currentScene_ = sceneLoader_.getSceneWithID(SceneID::MAIN_MENU);
	currentScene_->setSceneManager(this);
}

void SceneManager::initLevels(GameObject* player)
{
	currentScene_ = sceneLoader_.getSceneWithID(SceneID::LEVEL);
	currentScene_->setPlayer(player);
	currentScene_->setSceneManager(this);
	// ew
	static_cast<LevelManager*>(currentScene_)->initStartingLevel();
}

void SceneManager::setNextScene(SceneID sceneID)
{
	nextSceneID_ = sceneID;
}

void SceneManager::handleInput(SDL_Event& e)
{
	currentScene_->handleInput(e);
}

void SceneManager::update()
{
	currentScene_->update();
	if (nextSceneID_ != SceneID::INVALID)
	{
		currentScene_->onExit();
		//currentScene_ = levelLoader_.getLevelWithID(nextLevelID_);
		currentScene_ = sceneLoader_.getSceneWithID(nextSceneID_);
		currentScene_->setSceneManager(this);
		currentScene_->setPlayer(player_, player_->getPos());
		currentScene_->onEnter();
		nextSceneID_ = SceneID::INVALID;
	}
	
	//if (nextSceneID_ == SceneID::GAME_OVER)
	//{
	//	currentScene_->onExit();
	//	currentScene_ = &gameOverScene_;
	//	auto obj = currentScene_->gameObjects.add("Background", "GameOverScreen");
	//	currentScene_->setCameraFollowObject(obj.get());
	//	currentScene_->setSceneManager(this);
	//	currentScene_->setPlayer(player_);
	//	currentScene_->onEnter();
	//	nextSceneID_ = SceneID::INVALID;
	//}
}

void SceneManager::render(GameWindow& window, float percBehind)
{
	currentScene_->render(window, percBehind);
}

int SceneManager::getWidth()
{
	return currentScene_->getWidth();
}

int SceneManager::getHeight()
{
	return currentScene_->getHeight();
}
