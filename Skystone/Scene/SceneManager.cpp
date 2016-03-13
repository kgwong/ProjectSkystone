#include "SceneManager.h"



SceneManager::SceneManager()
	:nextSceneID_(SceneID::INVALID)
{
	currentScene_ = &levelManager_;
}


SceneManager::~SceneManager()
{
}

GameObject* SceneManager::cameraFollowObject()
{
	return currentScene_->cameraFollowObject();
}

void SceneManager::setPlayer(GameObject* player)
{
	player_ = player;
	levelManager_.setPlayer(player);
	levelManager_.initStartingLevel();
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
		currentScene_->setSceneManager(this);
		currentScene_->setPlayer(player_);
		currentScene_->onEnter();
		nextSceneID_ = SceneID::INVALID;
	}
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
