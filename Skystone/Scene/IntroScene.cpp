#include "IntroScene.h"
#include "Scene/SceneManager.h"


IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::onExit()
{
	sceneManager_->unload(SceneID::INTRO);
}
