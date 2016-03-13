#include "NonUpdatingComponent.h"



NonUpdatingComponent::NonUpdatingComponent(GameObject& owner)
	:Component(owner)
{
}


NonUpdatingComponent::~NonUpdatingComponent()
{
}

void NonUpdatingComponent::update(Scene& scene)
{
}

Component::Type NonUpdatingComponent::getType()
{
	return Component::Type::NON_UPDATING;
}
