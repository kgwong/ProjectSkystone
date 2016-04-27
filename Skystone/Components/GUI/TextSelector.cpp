#include "TextSelector.h"
#include "Game/GameInputs.h"


TextSelector::TextSelector(GameObject& owner)
	: InputComponent(owner), selected_(0), texts_(0)
{
}


TextSelector::~TextSelector()
{
}

void TextSelector::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, ControlType::DOWN) && selected_ < ((int)texts_.size()-1))
	{
		texts_.at(selected_++)->setSelected(false);
		texts_.at(selected_)->setSelected(true);
	}
	else if (GameInputs::keyDown(e, ControlType::UP) && selected_ > 0)
	{
		texts_.at(selected_--)->setSelected(false);
		texts_.at(selected_)->setSelected(true);
	}
	else if (GameInputs::keyDown(e, ControlType::RETURN))
	{
		scene.setNextScene(texts_.at(selected_)->getSceneOnSelection());
	}
}

void TextSelector::addText(std::shared_ptr<SelectableText> text)
{
	texts_.push_back(text);
	// always select the first one added
	if (texts_.size() == 1)
		texts_.at(0)->setSelected(true);
}
