#include "SwingingAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "GameMath/CircleMath.h"
#include <iostream>

SwingingAIComponent::SwingingAIComponent(GameObject& owner) :
	AIComponent(owner),
	radius_(168), stepRadius_(1), center_(Point{ 350,32 }), originalPosition_(Point{ 350,200 }),
	currentPosition_(originalPosition_), direction_(1),
	minAngle_(DEFAULT_MIN_ANGLE), maxAngle_(DEFAULT_MAX_ANGLE),
	currentAngle_(0), angleVelocity_(ANGULAR_VELOCITY),
	isHit_(false), timer_(0)
{
}

SwingingAIComponent::~SwingingAIComponent()
{	
}

void SwingingAIComponent::start(Level& level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	
	//setpoints here
	owner_.setPos(currentPosition_);
	physics_->enableGravity(false);


	//testing bullet capabilities here.
	Point location;
	location.x = 375;
	location.y = 100;
	level.addPlayerProjectileAtLocation(location, 2, 45);


	//std::cout << currentPosition_.x << ", " << currentPosition_.y << std::endl;
}

void SwingingAIComponent::update(Level& level)
{
	//increase length of rope
	//radius_ += stepRadius_;

	//trial 3
	if (isHit_)
	{
		++timer_;
		if (timer_ % 10 == 0 && maxAngle_ > 0 && minAngle_ < 0)
		{
			--maxAngle_;
			++minAngle_;
		}
		if (timer_ % TIME_TO_SWING == 0 && angleVelocity_ > 1)
		{
			--angleVelocity_;
		}
		if (angleVelocity_ == 1 && timer_ >= TIME_TO_SWING * 4)
		{
			isHit_ = false;
			angleVelocity_ = ANGULAR_VELOCITY;
			maxAngle_ = DEFAULT_MAX_ANGLE;
			minAngle_ = DEFAULT_MIN_ANGLE;
			timer_ = 0;
			currentPosition_ = originalPosition_;	
		}
		else
		{
			currentPosition_.x = center_.x + sin(toRadians(currentAngle_)) * radius_;
			currentPosition_.y = center_.y + cos(toRadians(currentAngle_)) * radius_;
		}
		
		//std::cout << currentPosition_.x << ", " << currentPosition_.y << std::endl;

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

		owner_.setPos(currentPosition_);
	}
}

//handles collision events.
void SwingingAIComponent::handleEvent(const CollisionEvent & e)
{
	//in java I'm trying to make a super call.
	AIComponent::handleEvent(e);
	GameObject &other = e.getOtherObject();

	//if player shoots a projectile at me, i will swing crazy.
	if (other.getType() == GameObject::Type::PLAYER_PROJECTILE)
	{
		isHit_ = true;
		Point bulletPoint = other.getPos();
		Point ownerPoint = owner_.getPos();
		//if bullet shot from the left, mob swings to the right, otherwise mob swings to the left
		if (Point::getXDirection(ownerPoint, bulletPoint) > 0)
			direction_ = 1;
		else
			direction_ = -1;
	}
}


