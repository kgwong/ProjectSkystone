#include "SceneManager.h"



SceneManager::SceneManager()
	:currentScene_(nullptr),
	player_(nullptr),
	nextSceneID_(SceneID::INVALID)
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
	currentScene_ = sceneLoader_.getSceneWithID(SceneID::MAIN_MENU);
	currentScene_->setSceneManager(this);
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
	if (nextSceneID_ != SceneID::INVALID && !hasQuitGame())
	{
		currentScene_->onExit();
		currentScene_ = sceneLoader_.getSceneWithID(nextSceneID_);
		currentScene_->setSceneManager(this);
		currentScene_->setPlayer(player_, player_->getPos());
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

bool SceneManager::hasQuitGame()
{
	return nextSceneID_ == SceneID::QUIT_GAME;
}

void SceneManager::unload(SceneID sceneID)
{
	sceneLoader_.unload(sceneID);
}