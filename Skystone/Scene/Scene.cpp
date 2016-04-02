#include "Scene.h"

#include "SceneManager.h"
#include "Game/GameConstants.h"

Scene::Scene()
	: gameObjects(*this, componentSystem_),
	cameraFollowObject_(nullptr)
{
}


Scene::~Scene()
{
}

void Scene::setCameraFollowObject(GameObject* object)
{
	cameraFollowObject_ = object;
}

GameObject* Scene::getCameraFollowObject()
{
	return cameraFollowObject_;
}

void Scene::setNextScene(SceneID sceneID)
{
	sceneManager_->setNextScene(sceneID);
}

void Scene::setSceneManager(SceneManager* sceneManager)
{
	sceneManager_ = sceneManager;
}

void Scene::onEnter()
{

}

void Scene::onExit()
{

}

void Scene::setPlayer(GameObject* player)
{
	setPlayer(player, Point{ 0,0 });
}

void Scene::setPlayer(GameObject* player, const Point& startPos)
{
	gameObjects.setPlayer(player);
	player->setPos(startPos);
}

void Scene::handleInput(SDL_Event& e)
{
	componentSystem_.handleInput(*this, e);
}

void Scene::update()
{
	componentSystem_.update(*this);
	gameObjects.update();
}

void Scene::render(GameWindow& window, float percBehind)
{
	componentSystem_.render(*this, window, percBehind);
}

int Scene::getWidth()
{
	return Constants::SCREEN_WIDTH;
}

int Scene::getHeight()
{
	return Constants::SCREEN_WIDTH;
}
