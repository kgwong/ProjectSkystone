#include "BasicEnemyMovementComponent.h"

#include "PhysicsComponent.h"

BasicEnemyMovementComponent::BasicEnemyMovementComponent()
	: speed_(DEFAULT_SPEED)
{
}

BasicEnemyMovementComponent::BasicEnemyMovementComponent(int speed)
	:speed_(speed)
{
}

BasicEnemyMovementComponent::~BasicEnemyMovementComponent()
{
}


void BasicEnemyMovementComponent::start(GameObject& owner, Level& level)
{
	physics_ = owner.getComponent<PhysicsComponent>();
	oldEnemyPosition_ = owner.getPosX();
}

void BasicEnemyMovementComponent::update(GameObject& owner, Level& level)
{
	int moveDistance = 300;
	if (owner.getPosX() > oldEnemyPosition_ + moveDistance) //no magic numbers plz
	{
		speed_ = -speed_;
	}
	else if (owner.getPosX() < oldEnemyPosition_ - moveDistance)
	{
		speed_ = -speed_;
	}

	physics_->setVelX(speed_);

}