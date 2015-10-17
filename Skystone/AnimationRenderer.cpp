#include "AnimationRenderer.h"



AnimationRenderer::AnimationRenderer(TextureSheet* textureSheet)
	: textureSheet_(textureSheet), 
	currFrame_(0),
	drawSrc_(textureSheet->getFrame(currFrame_))
{
	drawDest_.w = drawSrc_->w;
	drawDest_.h = drawSrc_->h;
}

AnimationRenderer::~AnimationRenderer()
{
}

void AnimationRenderer::update(GameObject& owner)
{
	Point cameraPos = textureSheet_->getWindow()->getCamera().getPos();
	drawDest_.x = owner.getPosX() - cameraPos.x;
	drawDest_.y = owner.getPosY() - cameraPos.y;
	drawSrc_ = textureSheet_->getFrame(currFrame_);
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), drawSrc_, &drawDest_);

	incrementFrame();
}

int AnimationRenderer::getWidth()
{
	return drawSrc_->w;
}

int AnimationRenderer::getHeight()
{
	return drawSrc_->h;
}

void AnimationRenderer::incrementFrame()
{
	currFrame_ = (++currFrame_) % textureSheet_->getNumFrames();
}


