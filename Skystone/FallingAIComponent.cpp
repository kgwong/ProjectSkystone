#include "FallingAIComponent.h"
#include "PhysicsComponent.h"


FallingAIComponent::FallingAIComponent()
	:yVelocity_(DEFAULT_Y_VELOCITY),
	radius_(DEFAULT_RADIUS)
{
}

void FallingAIComponent::start(GameObject & owner, Level & level)
{
	physics_ = owner.getComponent<PhysicsComponent>();
}


void FallingAIComponent::update(GameObject & owner, Level & level)
{

	int dist = getDistance(owner.getPos(), level.getPlayerPos());
	int yDist = getYDirection(owner.getPos(), level.getPlayerPos());
	int xDist = getXDirection(owner.getPos(), level.getPlayerPos());

	if (AIComponent::isNearby(yDist, 100) && AIComponent::isNearby(xDist, 20))
	{
		physics_->enableGravity(true);
	}

	else
	{
		physics_->enableGravity(false);
		yVelocity_ = DEFAULT_RISE_VELOCITY;
		physics_->setVelY(yVelocity_);

	}

}

FallingAIComponent::~FallingAIComponent()
{
}
