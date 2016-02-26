#include "FallingAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "GameTypes/Point.h"

const float FallingAIComponent::DEFAULT_Y_VELOCITY = 0 * 60.0f;
const float FallingAIComponent::DEFAULT_RISE_VELOCITY = -3 * 60.0f;
const float FallingAIComponent::DEFAULT_X_RADIUS = 25;
const float FallingAIComponent::DEFAULT_Y_RADIUS = 100;

FallingAIComponent::FallingAIComponent(GameObject& owner)
	: AIComponent(owner), 
	yVelocity_(DEFAULT_Y_VELOCITY),
	xRadius_(DEFAULT_X_RADIUS),
	yRadius_(DEFAULT_Y_RADIUS),
	timer_(0),
	isFalling_(false)
{
}

FallingAIComponent::~FallingAIComponent()
{
}


void FallingAIComponent::start(Level& level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
}


void FallingAIComponent::update(Level& level)
{
	float dist = Point::getDistance(owner_.getPos(), level.getPlayerPos());
	float yDist = Point::getYDirection(owner_.getPos(), level.getPlayerPos());
	float xDist = Point::getXDirection(owner_.getPos(), level.getPlayerPos());

	if (AIComponent::isNearby(yDist, yRadius_) && AIComponent::isNearby(xDist, xRadius_))
	{
		physics_->enableGravity(true);
		isFalling_ = true;
	}
	else
	{
		if (!isFalling_)
		{
			physics_->enableGravity(false);
			yVelocity_ = DEFAULT_RISE_VELOCITY;
			physics_->setVelY(yVelocity_);
		}
		else
		{
			timer_++;
			timer_ = timer_ % DEFAULT_TIME_INTERVAL;
		}


		if (timer_ == 0)
			isFalling_ = false;

	}

}

