#ifndef SCENE_H
#define SCENE_H

#include "GameObject/GameObjectContainer.h"
#include "ComponentSystem/ComponentSystem.h"

class SceneManager;

enum class SceneID {
	INVALID,
	LEVEL,
	PAUSE,
	MAIN_MENU,
	INTRO,
	GAME_OVER,
	QUIT_GAME,
};

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	GameObjectContainer gameObjects;

public:
	void setCameraFollowObject(GameObject* object);
	virtual GameObject* getCameraFollowObject();
	void setNextScene(SceneID sceneID);

	void setSceneManager(SceneManager* sceneManager);

	virtual void onEnter();
	virtual void onExit(); 

	virtual void setPlayer(GameObject* player);
	virtual void setPlayer(GameObject* player, const Point& startPos);

	virtual void handleInput(SDL_Event& e);
	virtual void update();
	virtual void render(GameWindow& window, float percBehind);

	virtual int getWidth();
	virtual int getHeight();

protected:
	ComponentSystem componentSystem_;
	SceneManager* sceneManager_;
	GameObject* cameraFollowObject_;
};

#endif //SCENE_H
