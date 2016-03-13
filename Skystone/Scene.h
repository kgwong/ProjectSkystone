#ifndef SCENE_H
#define SCENE_H

#include "GameObject/GameObjectContainer.h"
#include "ComponentSystem/ComponentSystem.h"

enum class SceneID {
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
	GameObject* cameraFollowObject();
	void setNextScene(SceneID sceneID);

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
};

#endif //SCENE_H
