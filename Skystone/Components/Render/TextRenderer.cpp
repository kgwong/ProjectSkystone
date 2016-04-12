#include "TextRenderer.h"

#include "Application/GameWindow.h"
#include "Application/Log.h"
#include <SDL/SDL.h>

const static int defaultFontSize = 28;
//const static std::string defaultFontPath = "../Assets/Fonts/LDFComicSans.ttf";
const static std::string defaultFontPath = "../Assets/Fonts/MaiandraGDRegular.ttf";

TextRenderer::TextRenderer(GameObject& owner)
	: RenderComponent(owner), font_(TTF_OpenFont(defaultFontPath.c_str(), defaultFontSize)), text_("")
{
	if (font_ == nullptr)
		LOG("Warning") << "No font loaded: " << TTF_GetError();
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::render(GameWindow& window, float percentBehind)
{
	if (text_ != "")
	{
		SDL_Color color = { 255, 255, 255 };
		SDL_Surface* message = TTF_RenderText_Blended(font_, text_.c_str(), color);
		SDL_Texture* text_texture = SDL_CreateTextureFromSurface(window.getRenderer(), message);

		int w, h;
		SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

		SDL_Rect src = { 0,0, w, h };
		SDL_Rect dest = { (int)owner_.getPosX()-(w/2), (int)owner_.getPosY()-(h/2), w, h };
		window.render(text_texture, &src, &dest);
		SDL_FreeSurface(message);
		SDL_DestroyTexture(text_texture);
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
	font_ = TTF_OpenFont(defaultFontPath.c_str(), size);
}