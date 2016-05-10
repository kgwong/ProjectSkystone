#include "GameOverScene.h"
#include "Scene/SceneManager.h"

GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::onEnter()
{
	gameObjects.getPlayer().setAlive(true);
	GameObjectBuilder::buildPlayer(gameObjects.getPlayer());
	sceneManager_->unload(SceneID::LEVEL);
}