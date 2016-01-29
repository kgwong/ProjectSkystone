#include "NonUpdatingComponent.h"



NonUpdatingComponent::NonUpdatingComponent(GameObject& owner)
	:Component(owner)
{
}


NonUpdatingComponent::~NonUpdatingComponent()
{
}

void NonUpdatingComponent::update(Level & level)
{
}

Component::Type NonUpdatingComponent::getType()
{
	return Component::Type::NON_UPDATING;
}
