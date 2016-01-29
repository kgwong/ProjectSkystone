#include "InputComponent.h"


InputComponent::InputComponent(GameObject& owner)
	: Component(owner)
{
}

InputComponent::~InputComponent()
{
}

Component::Type InputComponent::getType()
{
	return Component::Type::INPUT;
}
