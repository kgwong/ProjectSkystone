#include "UpdatingComponent.h"



UpdatingComponent::UpdatingComponent(GameObject& owner)
	: Component(owner)
{
}


UpdatingComponent::~UpdatingComponent()
{
}

void UpdatingComponent::handleEvent(const CollisionEvent & other)
{
}

Component::Type UpdatingComponent::getType()
{
	return Component::Type::UPDATING;
}
