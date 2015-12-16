#include "CollisionEvent.h"



CollisionEvent::CollisionEvent(Level& level, GameObject& other, ColliderComponent& otherCollider)
	:ComponentEvent(ComponentEvent::Type::onCollision, level),
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