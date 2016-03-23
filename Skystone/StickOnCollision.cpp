#include "StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"
#include "Game/GameConstants.h"
#include "Scene/Level/Level.h"

StickOnCollision::StickOnCollision(GameObject& owner)
	:Component(owner)
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
		LOG("INFO") << "Hook is connected at " << hookPoint;
		
	}
}

void StickOnCollision::update(Scene& scene)
{
	
	if (isConnected)
	{
		Level& level = static_cast<Level&>(scene);
		Point hookPoint = level.playerHook->getPos();
		Point playerPoint = scene.gameObjects.getPlayer().getPos();
		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(false);

		//here I want to see if the hook is touching a block.	
		//if (_hookActive)
		//{
		//	if (hook_collision && hook_collision->isConnected)
		//	{
		//		LOG("INFO") << "Hook Position" << level.playerHook->getPos();
		//		Point hookPoint = level.playerHook->getPos();
		//		Point playerPoint = scene.gameObjects.getPlayer().getPos();
		//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(false);
		//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->setAccelX(0.1);
		//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->setAccelY(0.1);
		//	}
		//	else
		//	{
		//		_hookActive = false;
		//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(true);
		//	}
		//	
		//}
		//else
		//{
		//	_hookActive = false;
		//	scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(true);
		//}
	}
}

Component::Type StickOnCollision::getType()
{
	return Component::Type::UPDATING;
}
