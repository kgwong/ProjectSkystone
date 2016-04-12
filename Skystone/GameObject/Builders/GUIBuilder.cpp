#include "GUIBuilder.h"

#include "Resources/Resources.h"
#include "Application/Log.h"
#include "Components/Render/TextSelector.h"
#include "Components/Render/SelectableText.h"
#include "Components/Scene/InputSceneChanger.h"
#include "Scene/Scene.h"

GUIBuilder::GUIBuilder()
{
}


GUIBuilder::~GUIBuilder()
{
}

std::shared_ptr<GameObject> GUIBuilder::build(ComponentSystem& componentSystem, const std::string& name, GameObject* player, GameObject* wrapper)
{
	auto gui = std::make_shared<GameObject>();
	auto& guiToBuild = *gui;

	guiToBuild.setType(GameObject::Type::GUI);
	auto textSelector = wrapper->getComponent<TextSelector>();

	if (name == "StartGameButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Start game");
		text->setSceneOnSelection(SceneID::LEVEL);
		textSelector->addText(text);
	}
	else if (name == "ExitGameButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Exit");
		text->setSceneOnSelection(SceneID::QUIT_GAME);
		textSelector->addText(text);
	}
	else if (name == "ExitToDesktopButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Exit to desktop");
		text->setSceneOnSelection(SceneID::QUIT_GAME);
		textSelector->addText(text);
	}
	else if (name == "ExitToMainMenuButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Exit to main menu");
		text->setSceneOnSelection(SceneID::MAIN_MENU);
		textSelector->addText(text);
	}
	else if (name == "ContinueGameButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Continue");
		text->setSceneOnSelection(SceneID::LEVEL);
		textSelector->addText(text);
	}
	else if (name == "InvisibleContinueOnEscButton") // invisible isn't really gui
	{
		guiToBuild.addComponent(componentSystem.getNew<InputSceneChanger>(guiToBuild, ESC, SceneID::LEVEL));
	}
	else
	{
		LOG("Warning") << "Invalid GUI name: " << name << ", nothing added";
	}
	return gui;
}