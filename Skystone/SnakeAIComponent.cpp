#include "SnakeAIComponent.h"
#include "PhysicsComponent.h"
#include <iostream>
using namespace std;
SnakeAIComponent::SnakeAIComponent()
	:velocity_(DEFAULT_VELOCITY)
{
}


SnakeAIComponent::~SnakeAIComponent()
{
}

void SnakeAIComponent::start(GameObject & owner, Level & level)
{
	physics_ = owner.getComponent<PhysicsComponent>();
	physics_->enableGravity(false);
	physics_->setVelX(velocity_);
	cornerPosition_ = owner.getPos();
}

void SnakeAIComponent::update(GameObject & owner, Level & level)
{
	cout << std::to_string(getXDistance(owner.getPos(), cornerPosition_)) + " ";
	if (getXDistance(owner.getPos(), cornerPosition_) > DEFAULT_X_DIST)
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
		cornerPosition_ = owner.getPos();

	}

	if (getYDistance(owner.getPos(), cornerPosition_) > DEFAULT_Y_DIST)
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
		cornerPosition_ = owner.getPos();

	}

	


			
	
}