#include "RandomJumperComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "RNG.h"
#include <iostream>

RandomJumperComponent::RandomJumperComponent()
	: timeInterval_(0)
{
}


RandomJumperComponent::~RandomJumperComponent()
{
}

void RandomJumperComponent::start(GameObject& owner, Level & level)
{
	physics_ = owner.getComponent<PhysicsComponent>();
	
	oldVelX_ = physics_->getVelX();
	oldVelY_ = physics_->getVelY();
	std::cout << oldVelX_ << ", " << oldVelY_ << std::endl;
}

void RandomJumperComponent::update(GameObject& owner, Level & level)
{
	
	timeInterval_++;
	timeInterval_ = timeInterval_ % DEFAULT_TIME_INTERVAL;

	if (timeInterval_ == 0)
	{
		oldVelX_ = physics_->getVelX();
		oldVelY_ = physics_->getVelY();
		physics_->setVelX(15);
		physics_->setVelY(-50);
	}
	else
	{
		physics_->setVelX(oldVelX_);
		physics_->setVelY(oldVelY_);
	}
	
}
