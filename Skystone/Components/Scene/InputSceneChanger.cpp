#include "InputSceneChanger.h"



InputSceneChanger::InputSceneChanger(GameObject& owner, ControlType key, SceneID nextScene)
	: InputComponent(owner), keyToChangeOn_(key), nextScene_(nextScene)
{
}


InputSceneChanger::~InputSceneChanger()
{
}

void InputSceneChanger::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, keyToChangeOn_))
		scene.setNextScene(nextScene_);
}