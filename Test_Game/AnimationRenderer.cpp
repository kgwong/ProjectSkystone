#include "AnimationRenderer.h"


AnimationRenderer::AnimationRenderer(Animation* animation)
	:_animation(animation), _currFrame(0)
{
}

AnimationRenderer::~AnimationRenderer()
{
}

void AnimationRenderer::update(GameObject& owner)
{
	_animation->renderFrame(owner.getPos(), _currFrame);
	incrementFrame();
}

int AnimationRenderer::getWidth()
{
	return _animation->getWidth();
}

int AnimationRenderer::getHeight()
{
	return _animation->getHeight();
}

void AnimationRenderer::incrementFrame()
{
	_currFrame = (++_currFrame) % _animation->getNumFrames();
}


