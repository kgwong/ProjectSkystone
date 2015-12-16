#include "PickupComponent.h"



PickupComponent::PickupComponent(GameObject& owner)
	:NonUpdatingComponent(owner)
{
}


PickupComponent::~PickupComponent()
{
}

void PickupComponent::handleEvent(const CollisionEvent& e)
{
	GameObject& other = e.getOtherObject();
	if (other.getType() == GameObject::Type::PLAYER)
	{
		owner_.kill();
	}
}
