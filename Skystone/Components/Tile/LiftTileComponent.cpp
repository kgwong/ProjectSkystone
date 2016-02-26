#include "LiftTileComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Collider/ColliderComponent.h"
#include "Application/Log.h"
#include <iostream>
using namespace std;



LiftTileComponent::LiftTileComponent(GameObject & owner)
	: SpecialTileComponent(owner),
	xRadius_(DEFAULT_X_RADIUS),
	time_(0),
	delay_(DEFAULT_DELAY),
	lift_(DEFAULT_LIFT),
	physics_(owner_.getComponent<PhysicsComponent>()),
	collider_(owner_.getComponent<ColliderComponent>())

{
}


LiftTileComponent::~LiftTileComponent()
{
}

void LiftTileComponent::start(Level & level)
{
	playerPhysics_ = level.player->getComponent<PhysicsComponent>();
	playerCollider_ = level.player->getComponent<ColliderComponent>();


}

void LiftTileComponent::update(Level & level)
{

	if (!playerPhysics_->gravityEnabled() && time_ >= delay_)
	{
		playerPhysics_->setAccelY(0);
		playerPhysics_->enableGravity(true);
		time_ = 0;

	}
	else
		time_++;
}

void LiftTileComponent::handleEvent(const CollisionEvent & other)
{
	tileRight_ = collider_->getRight() + 25;
	tileLeft_ = collider_->getLeft() - 25;


	if (other.getOtherObject().getType() == GameObject::Type::PLAYER && collider_->getTop() == playerCollider_->getBottom() && 
		playerCollider_->getRight() < tileRight_ && playerCollider_->getLeft() > tileLeft_)
	{
		
		playerPhysics_->enableGravity(false);
		playerPhysics_->setVelY(-DEFAULT_LIFT * 360);
	}

}

