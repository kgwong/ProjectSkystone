#ifndef SCENE_H
#define SCENE_H

#include "GameObject/GameObjectContainer.h"
#include "ComponentSystem/ComponentSystem.h"

class SceneManager;

enum class SceneID {
	INVALID,
	LEVEL,
	GAME_OVER
};

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	GameObjectContainer gameObjects;

public:
	virtual GameObject* cameraFollowObject();
	void setNextScene(SceneID sceneID);

	void setSceneManager(SceneManager* sceneManager);

	virtual void onEnter();
	virtual void onExit(); 

	void setPlayer(GameObject* player);
	void setPlayer(GameObject* player, const Point& startPos);

	virtual void handleInput(SDL_Event& e);
	virtual void update();
	virtual void render(GameWindow& window, float percBehind);

	virtual int getWidth();
	virtual int getHeight();

protected:
	ComponentSystem componentSystem_;

private:
	SceneManager* sceneManager_;
};

#endif //SCENE_H
