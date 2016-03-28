#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Level/LevelManager.h"

class Player;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	GameObject* getCameraFollowObject();
	void setPlayer(GameObject* player);
	void setNextScene(SceneID sceneID);

	void handleInput(SDL_Event& e);
	void update();
	void render(GameWindow& window, float percBehind);

	int getWidth();
	int getHeight();

private:
	Scene* currentScene_;
	GameObject* player_;

	LevelManager levelManager_;
	Scene gameOverScene_;


	SceneID nextSceneID_;
};

#endif //SCENE_MANAGER_H