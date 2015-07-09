#include "RenderComponent.h"


RenderComponent::RenderComponent(GameWindow* window)
	:_window(window)
{
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::setAnimation(Animation* animation)
{
	_animation = animation;
}

void RenderComponent::update(GameObject& owner)
{
	_animation->renderFrame(owner.getPosX(), owner.getPosY());
}


