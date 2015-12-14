#include "BasicEnemyMovementComponent.h"

#include "PhysicsComponent.h"

BasicEnemyMovementComponent::BasicEnemyMovementComponent(GameObject& owner)
	: AIComponent(owner),
	speed_(DEFAULT_SPEED)
{
}

BasicEnemyMovementComponent::BasicEnemyMovementComponent(GameObject& owner, int speed)
	: AIComponent(owner),
	speed_(speed)
{
}

BasicEnemyMovementComponent::~BasicEnemyMovementComponent()
{
}


void BasicEnemyMovementComponent::start(Level& level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	oldEnemyPosition_ = owner_.getPosX();
}

void BasicEnemyMovementComponent::update(Level& level)
{
	int moveDistance = 300;
	if (owner_.getPosX() > oldEnemyPosition_ + moveDistance)
	{
		speed_ = -speed_;
	}
	else if (owner_.getPosX() < oldEnemyPosition_ - moveDistance)
	{
		speed_ = -speed_;
	}

	physics_->setVelX(speed_);

}