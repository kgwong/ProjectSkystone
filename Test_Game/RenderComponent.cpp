#include "RenderComponent.h"


RenderComponent::RenderComponent(Animation* animation)
	:_animation(animation), _currFrame(0)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::update(GameObject& owner)
{
	_animation->renderFrame(owner.getPos(), _currFrame);
	incrementFrame();
}

void RenderComponent::incrementFrame()
{
	_currFrame = (++_currFrame) % _animation->getNumFrames();
}


