#include "TextRenderer.h"

#include "Application/GameWindow.h"
#include <SDL/SDL.h>

TextRenderer::TextRenderer(GameObject& owner)
	: RenderComponent(owner), font(nullptr)
{
	font = TTF_OpenFont("../Assets/Fonts/LDFComicSans.ttf", 28);
	//font = TTF_OpenFont("LDFComicSans.ttf", 28);
	if (font == nullptr)
		std::cout << TTF_GetError() << std::endl;;
}


TextRenderer::~TextRenderer()
{
}

void TextRenderer::render(GameWindow& window, float percentBehind)
{
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* message = TTF_RenderText_Blended(font, "", color);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(window.getRenderer(), message);

	int w, h;
	SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

	SDL_Rect src = { 0,0, w, h};
	SDL_Rect dest = { 0, 0, w, h};
	window.render(text_texture, &src, &dest);
}