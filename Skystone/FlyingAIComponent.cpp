#include "FlyingAIComponent.h"
#include "PhysicsComponent.h"


FlyingAIComponent::FlyingAIComponent(GameObject& owner)
	:AIComponent(owner),
	xVelocity_(DEFAULT_X_VELOCITY),
	yVelocity_(DEFAULT_Y_VELOCITY),
	timeInterval_(0)
{
}

FlyingAIComponent::~FlyingAIComponent()
{
}

void FlyingAIComponent::start(Level& level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void FlyingAIComponent::update(Level& level)
{
	physics_->enableGravity(false);
	timeInterval_++;
	timeInterval_ = timeInterval_ % DEFAULT_CHANGE_DIRECTION_TIME;

	if (timeInterval_ % (DEFAULT_CHANGE_DIRECTION_TIME / 6) == 0)
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
