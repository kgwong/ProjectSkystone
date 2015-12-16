#include "UpdatingComponent.h"



UpdatingComponent::UpdatingComponent(GameObject& owner)
	: Component(owner)
{
}


UpdatingComponent::~UpdatingComponent()
{
}

Component::Type UpdatingComponent::getType()
{
	return Component::Type::UPDATING;
}
