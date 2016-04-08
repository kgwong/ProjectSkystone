#include "CollisionEvent.h"

#include "ComponentEventReceiver.h"

CollisionEvent::CollisionEvent(Scene& scene, GameObject& other, ColliderComponent& otherCollider)
	: ComponentEvent(scene),
	other_(other),
	otherCollider_(otherCollider)
{
}

CollisionEvent::~CollisionEvent()
{
}

void CollisionEvent::dispatch(ComponentEventReceiver & eventReceiver) const
{
	eventReceiver.handleEvent(*this);
}

GameObject& CollisionEvent::getOtherObject() const
{
	return other_;
}

ColliderComponent& CollisionEvent::getOtherCollider() const
{
	return otherCollider_;
}