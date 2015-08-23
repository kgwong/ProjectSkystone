#include "SpriteRenderer.h"




SpriteRenderer::SpriteRenderer(GameWindow* window, 
	SDL_Texture* texture, 
	SDL_Rect drawSrc)
	: window_(window),
	texture_(texture),
	drawSrc_(drawSrc)
{
	drawDest_.w = drawSrc.w;
	drawDest_.h = drawSrc.h;
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::update(GameObject& owner)
{
	Point cameraPos = window_->camera.getPos();
	drawDest_.x = owner.getPosX() - cameraPos.x;
	drawDest_.y = owner.getPosY() - cameraPos.y;
	SDL_RenderCopy(window_->renderer, texture_, &drawSrc_, &drawDest_);
}

int SpriteRenderer::getWidth()
{
	return drawSrc_.w;
}

int SpriteRenderer::getHeight()
{
	return drawSrc_.h;
}
