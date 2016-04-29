#include "SwingingAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "GameMath/CircleMath.h"
#include <iostream>

static const float DELTA_TIME = 2.5;


SwingingAIComponent::SwingingAIComponent(GameObject& owner) :
	AIComponent(owner),
	radius_(168), stepRadius_(1), center_(Point{ 350,32 }), originalPosition_(Point{ 350,200 }),
	currentPosition_(originalPosition_), direction_(1),
	maxAngle_(DEFAULT_MAX_ANGLE),
	currentAngle_(0), angleVelocity_(3.141),
	isHit_(false), timer_(0)
{
}

SwingingAIComponent::~SwingingAIComponent()
{	
}

void SwingingAIComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	
	//setpoints here
	owner_.setPos(currentPosition_);
	physics_->enableGravity(false);

	//calculate rope length
	radius_ = abs(originalPosition_.y - center_.y);
	//calculate period of oscilation
	//~ keep in here as long as radius_ does not change per update.
	swingTime_ = 2 * (float)PI * sqrtf(radius_ / physics_->GRAVITY);
	//swingTime_ *= 2 * (float)PI;
	//initial angle. ~ some physics formula.
	currentAngle_ = maxAngle_ * sinf(sqrt(physics_->GRAVITY / radius_) * swingTime_);

	//damp coeficcient
	damp = .075;


	//testing bullet capabilities here.
	//Point location;
	//location.x = 375;
	//location.y = 100;
	//level.addPlayerProjectileAtLocation(location, 2, 45);

	/*std::cout << swingTime_ << std::endl;*/
	/*std::cout << "currentPosition: " << currentPosition_.x << ", " << currentPosition_.y << std::endl;
	std::cout << "currentAngle: " << currentAngle_ << std::endl;
	std::cout << "maxAngle: " << maxAngle_ << std::endl;
	std::cout << "angleVelocity: " << angleVelocity_ << std::endl;
*/
	//std::cout << currentPosition_.x << ", " << currentPosition_.y << std::endl;
}

void SwingingAIComponent::update(Scene& scene)
{
	//increase length of rope
	//radius_ += stepRadius_;

	//overload point to be printed out.

	if (isHit_)
	{
	/*	std::cout << "timer: " << timer_ << std::endl;
		std::cout << "swingTime: " << swingTime_ << std::endl;
		std::cout << "currentPosition: " << currentPosition_.x << ", " << currentPosition_.y << std::endl;
		std::cout << "currentAngle: " << currentAngle_ << std::endl;
		std::cout << "maxAngle: " << maxAngle_  << std::endl;
		std::cout << "angleVelocity: " << angleVelocity_ << std::endl;
		*/
		if (currentAngle_ > maxAngle_)
		{
			currentAngle_ = maxAngle_;
			direction_ = -direction_;
		}
		if (currentAngle_ < -maxAngle_)
		{
			currentAngle_ = -maxAngle_;
			direction_ = -direction_;
		}

		if (direction_ > 0)
			currentAngle_ += angleVelocity_;
		if (direction_ < 0)
			currentAngle_ -= angleVelocity_;

		currentPosition_.x = center_.x + sin(toRadians(currentAngle_)) * radius_;
		currentPosition_.y = center_.y + cos(toRadians(currentAngle_)) * radius_;

		if (timer_ >= swingTime_ * 8)
		{
			timer_ = 0;
			//isHit_ = false;
			maxAngle_ -= maxAngle_ * damp;
			angleVelocity_ -= angleVelocity_ * damp;
		}

		//resets
		if (maxAngle_ < 5)
		{
			isHit_ = false;
			maxAngle_ = DEFAULT_MAX_ANGLE;
			angleVelocity_ = 3.141;
		}

		timer_ += 2.5;
		//last part.
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


