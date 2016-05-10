#include "TextRenderer.h"

#include "Application/GameWindow.h"
#include "Application/Log.h"
#include <SDL/SDL.h>
#include <cmath>

#define OUTLINE_SIZE 1 

const static std::string defaultFontPath = "../Assets/Fonts/coolvetica.ttf";
const static SDL_Color defaultTextColor = { 255, 255, 255 };
const static SDL_Color defaultOutlineColor = { 0, 0, 0 };

TextRenderer::TextRenderer(GameObject& owner)
	: RenderComponent(owner),
	font_(TTF_OpenFont(defaultFontPath.c_str(), DEFAULT_FONT_SIZE)),
	outline_(TTF_OpenFont(defaultFontPath.c_str(), DEFAULT_FONT_SIZE)),
	textColor_(defaultTextColor), outlineColor_(defaultOutlineColor),
	text_("")
{
	TTF_SetFontOutline(outline_, OUTLINE_SIZE);

	if (font_ == nullptr)
		LOG("Warning") << "No font loaded: " << TTF_GetError();
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::render(GameWindow& window, float percentBehind)
{
	// Always create a new texture, even when it hasn't changed
	// Cache them in a map<string, texture> ?

	if (text_ != "")
	{
		SDL_Texture* textTexture = getTextTexture(window);
		SDL_Texture* outlineTexture = getOutlineTexture(window);

		renderOutline(window, outlineTexture);
		renderText(window, textTexture);

		SDL_DestroyTexture(textTexture);
		SDL_DestroyTexture(outlineTexture);
	}
}

std::string TextRenderer::getText()
{
	return text_;
}

void TextRenderer::setText(const std::string& newText)
{
	text_ = newText;
}

void TextRenderer::setFontSize(int size)
{
	TTF_CloseFont(font_);
	TTF_CloseFont(outline_);
	font_ = TTF_OpenFont(defaultFontPath.c_str(), size);
	outline_ = TTF_OpenFont(defaultFontPath.c_str(), size);
	TTF_SetFontOutline(outline_, OUTLINE_SIZE);
}

void TextRenderer::setTextColor(SDL_Color color)
{
	textColor_ = color;
}

void TextRenderer::setOutlineColor(SDL_Color color)
{
	outlineColor_ = color;
}

SDL_Texture* TextRenderer::getTextTexture(GameWindow& window)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font_, text_.c_str(), textColor_);
	SDL_Texture* result = SDL_CreateTextureFromSurface(window.getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
	return result;
}

SDL_Texture* TextRenderer::getOutlineTexture(GameWindow& window)
{
	SDL_Surface* outlineSurface = TTF_RenderText_Blended(outline_, text_.c_str(), outlineColor_);
	SDL_Texture* result = SDL_CreateTextureFromSurface(window.getRenderer(), outlineSurface);
	SDL_FreeSurface(outlineSurface);
	return result;
}

void TextRenderer::renderText(GameWindow& window, SDL_Texture* text)
{
	int w, h;
	SDL_QueryTexture(text, NULL, NULL, &w, &h);

	double wd = w;
	double hd = h;

	SDL_Rect src = { 0,0, w, h };
	SDL_Rect dest = { (int)(owner_.getPosX() - std::floor(wd/2)), (int)(owner_.getPosY()- std::floor(hd/2)), w, h };
	window.render(text, &src, &dest);
}

void TextRenderer::renderOutline(GameWindow& window, SDL_Texture* outline)
{
	int w, h;
	SDL_QueryTexture(outline, NULL, NULL, &w, &h);

	double wd = w;
	double hd = h;

	SDL_Rect src = { 0,0, w, h };
	SDL_Rect dest = { (int)(owner_.getPosX() - std::floor(wd/2)), (int)(owner_.getPosY() - std::ceil(hd/2)), w, h };
	window.render(outline, &src, &dest);
}