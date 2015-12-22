#include "SpriteRenderer.h"

#include "GameWindow.h"

SpriteRenderer::SpriteRenderer(GameObject& owner, TextureSheet* textureSheet)
	:RenderComponent(owner),
	textureSheet_(textureSheet),
	drawSrc_(textureSheet->getFrame(0)),
	drawDest_{0, 0, drawSrc_->w, drawSrc_->h}
{
}

SpriteRenderer::SpriteRenderer(GameObject& owner, TextureSheet* textureSheet,
	int textureIndex)
	:RenderComponent(owner),
	textureSheet_(textureSheet),
	drawSrc_(textureSheet->getFrame(textureIndex)),
	drawDest_{ 0, 0, drawSrc_->w, drawSrc_->h }
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::update(Level& level)
{
	Point cameraPos = textureSheet_->getWindow()->getCamera().getPos();
	drawDest_.x = owner_.getPosX() - cameraPos.x;
	drawDest_.y = owner_.getPosY() - cameraPos.y;
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), drawSrc_, &drawDest_);
}

int SpriteRenderer::getWidth()
{
	return drawSrc_->w;
}

int SpriteRenderer::getHeight()
{
	return drawSrc_->h;
}

void SpriteRenderer::changeSprite(TextureSheet* textureSheet)
{

}
