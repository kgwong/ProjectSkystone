#include "PounceAIComponent.h"
#include <math.h> 
#include "Components/Physics/PhysicsComponent.h"
#include "GameTypes/Point.h"
#include "Game/GameTime.h"
#include "Application/Log.h"





PounceAIComponent::PounceAIComponent(GameObject& owner)
	:AIComponent(owner),
	radius_(DEFAULT_RADIUS),
	cooldown_time_(DEFAULT_COOLDOWN_TIME),
	timer_(0)
{
}


PounceAIComponent::~PounceAIComponent()
{
}


void PounceAIComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	cooldown_ = true;
}

void PounceAIComponent::update(Scene& scene)
{
	//check if we're on cooldown; if not, check if we're on top of the pounce
	//if not, check which direction to jump, then jump
	//the cooldown timer only continues when not jumping (sorta)

	if (timer_ > cooldown_time_)
	{
		timer_ = 0;
		cooldown_ = false;
	}


	if (!cooldown_)
	{
		float xDist = Point::getXDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
		float playerSide;


		playerSide = Point::getFacingDirection(xDist, owner_.getPos(), scene.gameObjects.getPlayer().getPos());

		if (AIComponent::isNearby(xDist, radius_))
		{
			physics_->setVelY(DEFAULT_JUMP_HEIGHT * 60.0f);
			physics_->setVelX(DEFAULT_JUMP_DISTANCE * playerSide * 60.0f);
			cooldown_ = true;
		}

	}
	else
	{
		timer_ += Time::getElapsedUpdateTimeSeconds();

		if (!physics_->isFalling())
		{
			physics_->setVelX(0);
		}
	}

}
