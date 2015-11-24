#include "AIjump.h"
#include "PhysicsComponent.h"


AIjump::AIjump():jumpvelocity_(DEFAULT_JUMP_VELOCITY),timer_(0)

{
}

void AIjump::start(GameObject & owner, Level & level)
{
	physics_ = owner.getComponent<PhysicsComponent>();
}

void AIjump::update(GameObject & owner, Level & level)
{
	if (timer_ == JUMP_INTERVAL)
	{
		if (!physics_->isFalling())
		{
			jumpvelocity_ = DEFAULT_JUMP_VELOCITY;

		}
		else
		{
			jumpvelocity_ = FALL_VELOCITY;

		}
		physics_->setVelY(jumpvelocity_);
		timer_ = 0;
	}
	timer_ += 1;

	physics_->setVelY(jumpvelocity_);
}


AIjump::~AIjump()
{
}
