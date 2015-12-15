#include "SwingingAIComponent.h"
#include "PhysicsComponent.h"
#include "CircleMath.h"
#include <iostream>

SwingingAIComponent::SwingingAIComponent() :
	radius_(168),stepRadius_(1), center_(Point{ 350,32 }), originalPosition_(Point{ 350,200 }),
	currentPosition_(originalPosition_), direction_(1),
	minAngle_(DEFAULT_MIN_ANGLE),maxAngle_(DEFAULT_MAX_ANGLE),
	currentAngle_(0),angleVelocity_(ANGULAR_VELOCITY)
{
}

SwingingAIComponent::~SwingingAIComponent()
{	
}

void SwingingAIComponent::start(GameObject& owner,Level& level)
{
	physics_ = owner.getComponent<PhysicsComponent>();
	
	//setpoints here
	owner.setPos(currentPosition_);
	physics_->enableGravity(false);

}

void SwingingAIComponent::update(GameObject& owner, Level& level)
{
	//increase length of rope
	//radius_ += stepRadius_;

	//trial 3
	if (!onHit)
	{
		currentPosition_.x = center_.x + sin(toRadians(currentAngle_)) * radius_;
		currentPosition_.y = center_.y + cos(toRadians(currentAngle_)) * radius_;

		//boundary coniditions
		if (currentAngle_ > maxAngle_)
		{
			currentAngle_ = maxAngle_;
			direction_ = -direction_;
		}
		if (currentAngle_ < minAngle_)
		{
			currentAngle_ = minAngle_;
			direction_ = -direction_;
		}

		//increment Angle velocity
		if (direction_ > 0)
			currentAngle_ += angleVelocity_;
		if (direction_ < 0)
			currentAngle_ -= angleVelocity_;


		owner.setPos(currentPosition_);
	}
}


