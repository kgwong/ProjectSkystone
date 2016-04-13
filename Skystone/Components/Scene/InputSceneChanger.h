#ifndef CHANGE_SCENE_ON_KEY
#define CHANGE_SCENE_ON_KEY

#include "Components/InputComponent.h"
#include "Game/GameInputs.h"

class InputSceneChanger : public InputComponent
{
public:
	InputSceneChanger(GameObject& owner, ControlType key, SceneID nextScene);
	virtual ~InputSceneChanger();

	virtual void handleInput(Scene& scene, SDL_Event& e);

private:
	ControlType keyToChangeOn_;
	SceneID nextScene_;
};

#endif // CHANGE_SCENE_ON_KEY

