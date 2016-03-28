#include "SnakeAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include <iostream>
using namespace std;

const float DEFAULT_X_DIST = 100;
const float DEFAULT_Y_DIST = 100;
const float DEFAULT_VELOCITY = 3;

SnakeAIComponent::SnakeAIComponent(GameObject& owner)
	:AIComponent(owner), 
	velocity_(DEFAULT_VELOCITY)
{
}


SnakeAIComponent::~SnakeAIComponent()
{
}

void SnakeAIComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	physics_->enableGravity(false);
	physics_->setVelX(velocity_);
	cornerPosition_ = owner_.getPos();
}

void SnakeAIComponent::update(Scene& scene)
{

	if (Point::getXDistance(owner_.getPos(), cornerPosition_) > DEFAULT_X_DIST)
	{
		
		if (physics_->getVelX() > 0)
		{
			physics_->setVelY(velocity_);
		}

		else
		{
			physics_->setVelY(-velocity_);
		}

		physics_->setVelX(0);
		cornerPosition_ = owner_.getPos();

	}

	if (Point::getYDistance(owner_.getPos(), cornerPosition_) > DEFAULT_Y_DIST)
	{
		if (physics_->getVelY() > 0)
		{
			physics_->setVelX(-velocity_);
		}

		else
		{
			physics_->setVelX(velocity_);
		}

		physics_->setVelY(0);
		cornerPosition_ = owner_.getPos();

	}

}