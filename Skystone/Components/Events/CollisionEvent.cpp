#include "CollisionEvent.h"



CollisionEvent::CollisionEvent(Scene& scene, GameObject& other, ColliderComponent& otherCollider)
	:ComponentEvent(ComponentEvent::Type::onCollision, scene),
	other_(other),
	otherCollider_(otherCollider)
{
}

CollisionEvent::~CollisionEvent()
{
}

GameObject& CollisionEvent::getOtherObject() const
{
	return other_;
}

ColliderComponent& CollisionEvent::getOtherCollider() const
{
	return otherCollider_;
}