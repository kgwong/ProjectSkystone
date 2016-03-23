#include "BasicEnemyMovementComponent.h"

#include "Components/Physics/PhysicsComponent.h"

const float BasicEnemyMovementComponent::DEFAULT_SPEED = 1 * 60.0f;

BasicEnemyMovementComponent::BasicEnemyMovementComponent(GameObject& owner)
	: AIComponent(owner),
	speed_(DEFAULT_SPEED)
{
}

BasicEnemyMovementComponent::BasicEnemyMovementComponent(GameObject& owner, float speed)
	: AIComponent(owner),
	speed_(speed)
{
}

BasicEnemyMovementComponent::~BasicEnemyMovementComponent()
{
}


void BasicEnemyMovementComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	oldEnemyPosition_ = owner_.getPosX();
}

void BasicEnemyMovementComponent::update(Scene& scene)
{
	float moveDistance = 300;
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