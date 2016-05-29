#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>
#include <SDL/SDL_ttf.h>
#include "Components/Render/RenderComponent.h"

class TextRenderer : public RenderComponent
{
public:
	enum class RenderMode {RENDER_FROM_CENTER, RENDER_FROM_TOP_LEFT};
	static const int DEFAULT_FONT_SIZE = 50;

	TextRenderer(GameObject& owner);
	virtual ~TextRenderer();
	virtual void render(GameWindow& window, float percBehind);

	std::string getText();
	TTF_Font* getFont();
	TTF_Font* getOutlineFont();

	void setText(const std::string& newText);
	void setFontSize(int size);
	void setRenderMode(RenderMode mode);
	void setTextColor(SDL_Color color);
	void setOutlineColor(SDL_Color color);

private:
	enum class TextTextureType{OUTLINE, TEXT};
	TTF_Font* font_, *outline_;
	SDL_Color textColor_, outlineColor_;
	std::string text_;
	RenderMode renderMode_;

	SDL_Texture* getTextTexture(GameWindow& window);
	SDL_Texture* getOutlineTexture(GameWindow& window);
	SDL_Rect getTextDest(double w, double h);
	void renderTextTexture(GameWindow& window, SDL_Texture* textTexture, TextTextureType type);
};

#endif //TEXT_RENDERER_H