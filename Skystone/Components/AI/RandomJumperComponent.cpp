#include "RandomJumperComponent.h"
#include "Components/Physics/PhysicsComponent.h"

#include "GameMath/RNG.h"

const float RandomJumperComponent::DEFAULT_JUMP_VELOCITY = -15 * 60;
const float RandomJumperComponent::DEFAULT_X_VELOCITY = 5 * 60;

RandomJumperComponent::RandomJumperComponent(GameObject& owner)
	: AIComponent(owner),
	timeInterval_(0),
	jumpVelocity_(DEFAULT_JUMP_VELOCITY),
	xVelocity_(DEFAULT_X_VELOCITY)
{
}


RandomJumperComponent::~RandomJumperComponent()
{
}

void RandomJumperComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void RandomJumperComponent::update(Scene& scene)
{
	xVelocity_ = RNG::getBool(0.5) ? xVelocity_ : -xVelocity_;
	
	timeInterval_++;
	timeInterval_ = timeInterval_ % DEFAULT_TIME_INTERVAL;

	if (timeInterval_ == 0)
	{		
		physics_->setVelX(xVelocity_);
		physics_->setVelY(jumpVelocity_);
	}
	else
	{
		if (!physics_->isFalling())
			physics_->setVelX(0);
	}





	
}
