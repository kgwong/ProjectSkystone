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

	void setTextColor(SDL_Color color);
	void setOutlineColor(SDL_Color color);

private:
	TTF_Font* font_;
	TTF_Font* outline_;

	SDL_Color textColor_, outlineColor_;
	std::string text_;


	SDL_Texture* getTextTexture(GameWindow& window);
	SDL_Texture* getOutlineTexture(GameWindow& window);

	void renderText(GameWindow& window, SDL_Texture* text);
	void renderOutline(GameWindow& window, SDL_Texture* outline);
};

#endif //TEXT_RENDERER_H