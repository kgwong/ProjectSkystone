#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>
#include "Components/Render/RenderComponent.h"

#include <SDL/SDL_ttf.h>

class TextRenderer : public RenderComponent
{
public:
	TextRenderer(GameObject& owner);
	virtual ~TextRenderer();
	virtual void render(GameWindow& window, float percentBehind);

	std::string getText();
	void setText(const std::string& newText);
	void setFontSize(int size);

private:
	TTF_Font* font_;
	std::string text_;
};

#endif //TEXT_RENDERER_H