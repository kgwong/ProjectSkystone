#include "StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"
#include "Components/Collider/ColliderComponent.h"
#include "Game/GameConstants.h"

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
		
		auto tileCollider = e.getOtherCollider();
		auto hookCollider = owner_.getComponent<ColliderComponent>();

		float hookBot = hookCollider->getBottom();
		float tileBot = tileCollider.getBottom();
		float tileTop = tileCollider.getTop();

		if (hookBot == tileTop)
		{
			isConnected = false;
		}
		else
		{
			isConnected = true;
		}
		//LOG("INFO") << "Hook is connected at " << hookPoint;
		
	}
}