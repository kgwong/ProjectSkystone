#include "GUIBuilder.h"

#include "Resources/Resources.h"
#include "Application/Log.h"
#include "Components/GUI/TextSelector.h"
#include "Components/GUI/SelectableText.h"
#include "Components/GUI/HealthBar.h"
#include "Components/Scene/InputSceneChanger.h"
#include "Scene/Scene.h"

GUIBuilder::GUIBuilder()
{
}


GUIBuilder::~GUIBuilder()
{
}

std::shared_ptr<GameObject> GUIBuilder::build(ComponentSystem& componentSystem, const std::string& name, GameObject* player)
{
	auto gui = std::make_shared<GameObject>();
	auto& guiToBuild = *gui;

	// all buttons are controlled by the most recently constructed TextSelector
	if (name == "TextSelector")
	{
		textSelector_ = gui = std::make_shared<GameObject>();
		auto& textSelectorToBuild = *textSelector_;
		textSelectorToBuild.setType(GameObject::Type::GUI);
		textSelectorToBuild.addComponent(componentSystem.getNew<TextSelector>(textSelectorToBuild));
	}
	else if (name == "StartGameButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Start game");
		text->setSceneOnSelection(SceneID::LEVEL);
		textSelector_->getComponent<TextSelector>()->addText(text);
	}
	else if (name == "ExitGameButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Exit");
		text->setSceneOnSelection(SceneID::QUIT_GAME);
		textSelector_->getComponent<TextSelector>()->addText(text);
	}
	else if (name == "ExitToDesktopButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Exit to desktop");
		text->setSceneOnSelection(SceneID::QUIT_GAME);
		textSelector_->getComponent<TextSelector>()->addText(text);
	}
	else if (name == "ExitToMainMenuButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Exit to main menu");
		text->setSceneOnSelection(SceneID::MAIN_MENU);
		textSelector_->getComponent<TextSelector>()->addText(text);
	}
	else if (name == "ContinueGameButton")
	{
		auto text = componentSystem.getNew<SelectableText>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("Continue");
		text->setSceneOnSelection(SceneID::LEVEL);
		textSelector_->getComponent<TextSelector>()->addText(text);
	}
	else if (name == "GameOverHeader")
	{
		auto text = componentSystem.getNew<TextRenderer>(guiToBuild);
		guiToBuild.addComponent(text);
		text->setText("GAME OVER");
		text->setFontSize((int)(TextRenderer::DEFAULT_FONT_SIZE * 1.5));
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