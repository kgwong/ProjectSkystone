#include "AIjump.h"
#include "Components/Physics/PhysicsComponent.h"

AIjump::AIjump(GameObject& owner)
	:AIComponent(owner),
	jumpvelocity_(DEFAULT_JUMP_VELOCITY),timer_(0)
{
}

AIjump::~AIjump()
{
}

void AIjump::start(Level& level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void AIjump::update(Level& level)
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
