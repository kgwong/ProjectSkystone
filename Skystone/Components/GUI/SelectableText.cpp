#include "SelectableText.h"

#define LARGE_TEXT_SIZE 80
#define SMALL_TEXT_SIZE 50 

SelectableText::SelectableText(GameObject& owner)
	: TextRenderer(owner), selected_(false)
{
}


SelectableText::~SelectableText()
{
}

bool SelectableText::isSelected()
{
	return selected_;
}

void SelectableText::setSelected(bool selected)
{
	selected_ = selected;
}

void SelectableText::render(GameWindow& window, float percBehind)
{
	if (selected_)
		setFontSize(LARGE_TEXT_SIZE);
	else
		setFontSize(SMALL_TEXT_SIZE);
	TextRenderer::render(window, percBehind);
}

void SelectableText::setSceneOnSelection(SceneID scene)
{
	sceneOnSelection_ = scene;
}

SceneID SelectableText::getSceneOnSelection()
{
	return sceneOnSelection_;
}