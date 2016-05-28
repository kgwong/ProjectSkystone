#ifndef TEXT_SELECTOR_H
#define TEXT_SELECTOR_H

#include "Components/InputComponent.h"
#include "Components/GUI/SelectableText.h"

#include <memory>

class TextSelector : public InputComponent
{
public:
	TextSelector(GameObject& owner);
	virtual ~TextSelector();

	virtual void handleInput(Scene& scene, SDL_Event& e);
	void addText(std::shared_ptr<SelectableText> text);

private:
	std::vector<std::shared_ptr<SelectableText>> texts_;
	int selected_;

	void selectNext();
	void selectPrev();
};

#endif // MAIN_MENU_TEXT_SELECTOR_H
