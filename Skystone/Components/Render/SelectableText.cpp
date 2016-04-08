#include "SelectableText.h"



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
		TextRenderer::setBg({ 255, 255, 0 });
	else
		TextRenderer::setBg({ 0,0,0 });
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