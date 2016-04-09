#include "StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"

StickOnCollision::StickOnCollision(GameObject& owner)
	:NonUpdatingComponent(owner),
	isConnected(false)
{
	hookPoint.x = -999;
	hookPoint.y = -999;
	
}

StickOnCollision::~StickOnCollision()
{
}

void StickOnCollision::handleEvent(const CollisionEvent& e)
 {

	GameObject obj = e.getOtherObject();
	if (obj.getType() == GameObject::Type::TILE)
	{
		hookPoint = obj.getPos();
		PhysicsComponent * hookPhysics = owner_.getComponent<PhysicsComponent>();
		hookPhysics->setVelX(0);
		hookPhysics->setVelY(0);
		isConnected = true;
		//LOG("INFO") << "Hook is connected at " << hookPoint;
		
	}
}