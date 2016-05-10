#include "MainMenu.h"
#include "Scene/SceneManager.h"
#include "Components/Common/HealthComponent.h"

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::onEnter()
{
	GameObjectBuilder::buildPlayer(gameObjects.getPlayer());
	sceneManager_->unload(SceneID::LEVEL);
}
