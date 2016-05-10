#include "PounceAIComponent.h"
#include <math.h> 
#include "Components/Physics/PhysicsComponent.h"
#include "GameTypes/Point.h"
#include "Game/GameTime.h"
#include "Application/Log.h"
#include "BossAIComponent.h"
#define SPEED 60.0f


PounceAIComponent::PounceAIComponent(GameObject& owner)
	: AIComponent(owner),
	radius_(DEFAULT_RADIUS),
	cooldown_time_(DEFAULT_COOLDOWN_TIME),
	timer_(0),
	enemy_type_(""),
	jump_distance_(DEFAULT_JUMP_DISTANCE),
	jump_height_(DEFAULT_JUMP_HEIGHT)
{
}

PounceAIComponent::PounceAIComponent(GameObject& owner, std::string enemyType)
	:AIComponent(owner),
	radius_(DEFAULT_RADIUS),
	cooldown_time_(DEFAULT_COOLDOWN_TIME),
	timer_(0),
	enemy_type_(enemyType),
	jump_distance_(DEFAULT_JUMP_DISTANCE),
	jump_height_(DEFAULT_JUMP_HEIGHT)
{
}


PounceAIComponent::~PounceAIComponent()
{
}


void PounceAIComponent::start(Scene& scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	boss_ = owner_.getComponent<BossAIComponent>();
	cooldown_ = true;
	if (enemy_type_ == "Boss")
	{
		cooldown_ = false;
	}
}

void PounceAIComponent::update(Scene& scene)
{
	float final_height_ = jump_height_;
	float final_distance_ = jump_distance_;

	if (enemy_type_ == "Boss")
	{
		float xDist = Point::getXDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());

		float distance_ratio = abs(xDist) / radius_;
		final_height_ = jump_height_ * distance_ratio;
		final_distance_ = jump_distance_ * distance_ratio;

		if (timer_ > boss_->getCooldown())
		{
			timer_ = 0;
			cooldown_ = false;
		}
	}

	//check if we're on cooldown; if not, check if we're on top of the pounce
	//if not, check which direction to jump, then jump
	//the cooldown timer only continues when not jumping (sorta)


	else if (timer_ > cooldown_time_)
	{
		timer_ = 0;
		cooldown_ = false;
	}


	if (!cooldown_)
	{
		float xDist = Point::getXDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
		float playerSide;

		playerSide = Point::getFacingDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
		LOG("AARON") << playerSide;
		if (enemy_type_ == "Boss")
		{
			boss_->getPhysics()->setVelY(final_height_ * SPEED);
			boss_->getPhysics()->setVelX(final_distance_ * playerSide * SPEED);

			
			
		}
		else if (AIComponent::isNearby(xDist, radius_))
		{
			physics_->setVelY(final_height_ * SPEED);
			physics_->setVelX(final_distance_ * playerSide * SPEED);
		}
		cooldown_ = true;
	}
	else
	{
		timer_ += Time::getElapsedUpdateTimeSeconds();
		if (!physics_->isFalling())
		{
			physics_->setVelX(0);
		}
		if (enemy_type_ == "Boss")
		{
			if (!boss_->getPhysics()->isFalling())
			{
				boss_->getPhysics()->setVelX(0);
				boss_->setAttack("Idle");
				cooldown_ = false;
			}
		}
	}

}
