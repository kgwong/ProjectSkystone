#include "FlyingAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"
#include "Game/GameTime.h"





const float FlyingAIComponent::DEFAULT_X_VELOCITY = 3 * 60.0f;
const float FlyingAIComponent::DEFAULT_Y_VELOCITY = -1 * 60.0f;
const float FlyingAIComponent::DEFAULT_X_DIRECTION_CHANGE = 2; //use Time::
const float FlyingAIComponent::DEFAULT_Y_DIRECTION_CHANGE = 0.4f;

FlyingAIComponent::FlyingAIComponent(GameObject& owner)
	:AIComponent(owner),
	xVelocity_(DEFAULT_X_VELOCITY),
	yVelocity_(DEFAULT_Y_VELOCITY),
	xchange_(0),
	ychange_(0)

{
}

FlyingAIComponent::~FlyingAIComponent()
{
}

void FlyingAIComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	physics_->enableGravity(false);
	physics_->setVelX(xVelocity_);
}

void FlyingAIComponent::update(Scene& scene)
{
	xchange_ += Time::getElapsedUpdateTimeSeconds();
	ychange_ += Time::getElapsedUpdateTimeSeconds();


	if (xchange_ > DEFAULT_X_DIRECTION_CHANGE)
	{
		xchange_ = 0;
		xVelocity_  =  xVelocity_ * -1;
		physics_->setVelX(xVelocity_);

	}

	if (ychange_  > DEFAULT_Y_DIRECTION_CHANGE )
	{
		ychange_ = 0;
		yVelocity_ = yVelocity_ * -1;
		physics_->setVelY(yVelocity_);

	}
}