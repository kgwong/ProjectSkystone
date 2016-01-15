#include "PounceAIComponent.h"
#include <math.h> 
#include "PhysicsComponent.h"
#define PI 3.14159265
#include <iostream>
using namespace std;

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
	timeInterval_++;
	timeInterval_ %= cooldown_time_;
	if (timeInterval_ == 0)
	{
		cooldown_ = false;
	}


	if (!cooldown_)
	{
		int xDist = getXDirection(owner_.getPos(), level.getPlayerPos());
		int playerSide;

		if (getXDistance(owner_.getPos(), level.getPlayerPos()) == 0)
		{
			playerSide = 0;
		}

		else
		{
			playerSide = -xDist / getXDistance(owner_.getPos(), level.getPlayerPos());
		}


		if (AIComponent::isNearby(xDist, radius_))
		{
			physics_->setVelY(-10);
			physics_->setVelX(playerSide * 7);
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
