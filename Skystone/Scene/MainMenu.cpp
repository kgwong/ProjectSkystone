#include "MainMenu.h"
#include "Scene/SceneManager.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::onEnter()
{
	sceneManager_->unload(SceneID::LEVEL);
}
