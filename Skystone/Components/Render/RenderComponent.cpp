#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject& owner)
	:Component(owner)
{

}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::start(Level& level)
{
	prevPosition = owner_.getPos();
}

void RenderComponent::update(Level& level)
{
	prevPosition = owner_.getPos();
}

Component::Type RenderComponent::getType()
{
	return Component::Type::RENDER;
}

int RenderComponent::getWidth()
{
	return 0;
}

int RenderComponent::getHeight()
{
	return 0;
}

int RenderComponent::getRenderLayer()
{
	switch (owner_.getType())
	{
	case GameObject::Type::BACKGROUND:
	case GameObject::Type::TILE:
		return 0;
	case GameObject::Type::ENEMY:
	case GameObject::Type::PLAYER_PROJECTILE:
	case GameObject::Type::PLAYER_HOOK:
	case GameObject::Type::ENEMY_PROJECTILE:
	case GameObject::Type::DROP:
		return 1;
	case GameObject::Type::PLAYER:
		return 2;
	default:
		return 9;
	}
}

Point RenderComponent::getRenderPosition(float percBehind)
{
	Point currPos = owner_.getPos();
	int estVelX = currPos.x - prevPosition.x;
	int estVelY = currPos.y - prevPosition.y;

	return Point(currPos.x + estVelX * percBehind, currPos.y + estVelY * percBehind);
}

