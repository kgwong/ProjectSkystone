#include "StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"

StickOnCollision::StickOnCollision(GameObject& owner)
	:NonUpdatingComponent(owner)
{
}

StickOnCollision::~StickOnCollision()
{
}

void StickOnCollision::handleEvent(const CollisionEvent& e)
{
	GameObject obj = e.getOtherObject();
	if (obj.getType() == GameObject::Type::TILE)
	{
		PhysicsComponent * hookPhysics = owner_.getComponent<PhysicsComponent>();
		hookPhysics->setVelX(0);
		hookPhysics->setVelY(0);
	}
}
