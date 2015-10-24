#include "BasicEnemyMovementComponent.h"

#include "PhysicsComponent.h"
#include "GameObject.h"

BasicEnemyMovementComponent::BasicEnemyMovementComponent()
	: speed_(DEFAULT_SPEED), initialized(false)
{
}

BasicEnemyMovementComponent::BasicEnemyMovementComponent(int speed)
	:speed_(speed), initialized(false)
{
}

BasicEnemyMovementComponent::~BasicEnemyMovementComponent()
{
}

void BasicEnemyMovementComponent::update(GameObject& owner) 
{
	PhysicsComponent* physics = owner.getComponent<PhysicsComponent>();

	if (!initialized)
	{
		oldEnemyPosition = owner.getPosX();
		initialized = true;
	}
	if (owner.getPosX() > oldEnemyPosition + 300)
	{
		speed_ = -speed_;
	}
	else if (owner.getPosX() < oldEnemyPosition - 300)
	{
		speed_ = -speed_;
	}

	physics->setVelX(speed_);

}