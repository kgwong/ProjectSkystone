#include "SpriteRenderer.h"




SpriteRenderer::SpriteRenderer(TextureSheet* textureSheet)
	:textureSheet_(textureSheet),
	drawSrc_(textureSheet->getFrame(0)),
	drawDest_{0, 0, drawSrc_->w, drawSrc_->h}
{
}

SpriteRenderer::SpriteRenderer(TextureSheet* textureSheet,
	int textureIndex)
	:textureSheet_(textureSheet),
	drawSrc_(textureSheet->getFrame(textureIndex)),
	drawDest_{ 0, 0, drawSrc_->w, drawSrc_->h }
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::update(GameObject& owner)
{
	Point cameraPos = textureSheet_->getWindow()->getCamera().getPos();
	drawDest_.x = owner.getPosX() - cameraPos.x;
	drawDest_.y = owner.getPosY() -cameraPos.y;
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
