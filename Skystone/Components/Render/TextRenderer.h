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
	void setText(std::string newText);
private:
	TTF_Font* font;
	std::string text;
};

#endif //TEXT_RENDERER_H
