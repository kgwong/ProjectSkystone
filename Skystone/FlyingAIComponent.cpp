#include "FlyingAIComponent.h"
#include "PhysicsComponent.h"


FlyingAIComponent::FlyingAIComponent()
	:xVelocity_(DEFAULT_X_VELOCITY),
	yVelocity_(DEFAULT_Y_VELOCITY),
	timeInterval_(0)
{
}

FlyingAIComponent::~FlyingAIComponent()
{
}


void FlyingAIComponent::start(GameObject & owner, Level & level)
{
	physics_ = owner.getComponent<PhysicsComponent>();
	physics_->enableGravity(false);
	physics_->setVelX(xVelocity_);

}

void FlyingAIComponent::update(GameObject & owner, Level & level)
{
	timeInterval_++;
	timeInterval_ = timeInterval_ % DEFAULT_X_DIRECTION_TIME;

	if (timeInterval_ % (DEFAULT_X_DIRECTION_TIME / DEFAULT_Y_DIRECTION_CHANGES) == 0)
	{
		yVelocity_ = yVelocity_ * -1;
		physics_->setVelY(yVelocity_);
	}

	if (timeInterval_ == 0)
	{
		xVelocity_ = xVelocity_ * -1;
		physics_->setVelX(xVelocity_);
	}
}

