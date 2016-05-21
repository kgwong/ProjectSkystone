#include "TextRenderer.h"

#include "Application/GameWindow.h"
#include "Application/Log.h"
#include <SDL/SDL.h>
#include <cmath>

#define OUTLINE_SIZE 1 

const static std::string defaultFontPath = "../Assets/Fonts/coolvetica.ttf";
const static SDL_Color defaultTextColor = { 255, 255, 255 };
const static SDL_Color defaultOutlineColor = { 0, 0, 0 }; 

namespace
{
TTF_Font* getDefaultFont()
{
	return TTF_OpenFont(defaultFontPath.c_str(), TextRenderer::DEFAULT_FONT_SIZE);
}
}


TextRenderer::TextRenderer(GameObject& owner)
	: RenderComponent(owner),
	font_(getDefaultFont()), outline_(getDefaultFont()),
	textColor_(defaultTextColor), outlineColor_(defaultOutlineColor),
	renderMode_(TextRenderer::RenderMode::RENDER_FROM_CENTER)
{
	TTF_SetFontOutline(outline_, OUTLINE_SIZE);
	if (font_ == nullptr)
		LOG("Warning") << "No font loaded: " << TTF_GetError();
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::render(GameWindow& window, float percBehind)
{
	// Always create a new texture, even when it hasn't changed
	// Cache them in a map<string, texture> ?
	if (text_ != "")
	{
		SDL_Texture* textTexture = getTextTexture(window);
		SDL_Texture* outlineTexture = getOutlineTexture(window);

		renderTextTexture(window, outlineTexture, TextTextureType::OUTLINE);
		renderTextTexture(window, textTexture, TextTextureType::TEXT);

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

void TextRenderer::setRenderMode(TextRenderer::RenderMode mode)
{
	renderMode_ = mode;
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

void TextRenderer::renderTextTexture(GameWindow& window, SDL_Texture* textTexture, TextTextureType type)
{
	int w, h;
	SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
	SDL_Rect src = { 0,0, w, h };
	SDL_Rect dest = getTextDest((double)w, (double)h);
	if(type == TextTextureType::OUTLINE)
		dest.y -= OUTLINE_SIZE;
	window.render(textTexture, &src, &dest);
}

SDL_Rect TextRenderer::getTextDest(double w, double h)
{
	SDL_Rect dest;
	if (renderMode_ == TextRenderer::RenderMode::RENDER_FROM_CENTER)
		dest = { (int)(owner_.getPosX() - std::floor(w / 2)), (int)(owner_.getPosY() - std::ceil(h / 2)), (int)w, (int)h };
	else
		dest = { (int)(owner_.getPosX()), (int)(owner_.getPosY()), (int)w, (int)h };
	return dest;
}