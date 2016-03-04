#include "PounceAIComponent.h"
#include <math.h> 
#include "Components/Physics/PhysicsComponent.h"
#include "GameTypes/Point.h"
#include "Game/GameTime.h"

#define PI 3.14159265


const float PounceAIComponent::DEFAULT_RADIUS = 175.0f;
const float PounceAIComponent::DEFAULT_COOLDOWN_TIME = 1.2;

PounceAIComponent::PounceAIComponent(GameObject& owner)
	:AIComponent(owner),
	radius_(DEFAULT_RADIUS),
	cooldown_time_(DEFAULT_COOLDOWN_TIME),
	timeInterval_(0)
{
}


PounceAIComponent::~PounceAIComponent()
{
}


void PounceAIComponent::start(Level& level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	cooldown_ = true;
}

void PounceAIComponent::update(Level& level)
{
	timeInterval_ += Time::getElapsedUpdateTimeSeconds();
	//UNTESTED
	if (timeInterval_ > cooldown_time_)
	{
		timeInterval_ = 0;
		cooldown_ = false;
	}


	if (!cooldown_)
	{
		float xDist = Point::getXDirection(owner_.getPos(), level.getPlayerPos());
		int playerSide;

		if (Point::getXDistance(owner_.getPos(), level.getPlayerPos()) == 0)
		{
			playerSide = 0;
		}

		else
		{
			playerSide = (int) (-xDist / Point::getXDistance(owner_.getPos(), level.getPlayerPos()));
		}


		if (AIComponent::isNearby(xDist, radius_))
		{
			physics_->setVelY(-10 * 60.0f);
			physics_->setVelX(playerSide * 7 * 60.0f);
			cooldown_ = true;
		}

	}
	else
	{
		if (!physics_->isFalling())
		{
			physics_->setVelX(0);
		}
	}

}
