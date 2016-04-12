#include "SlamAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Common/HealthComponent.h"
#include "Game/GameTime.h"
#include "Application/Log.h"
#include "BossAIComponent.h"
#define SPEED 60.0f

SlamAIComponent::SlamAIComponent(GameObject & owner) :
	AIComponent(owner),
	attack_initiated_(false),
	timer_(0),
	windup_time_(DEFAULT_WINDUP_TIME),
	windup_speed_(DEFAULT_WINDUP_SPEED),
	swing_speed_(DEFAULT_SWING_SPEED),
	swing_time_(DEFAULT_SWING_TIME),
	lag_time_(DEFAULT_LAG_TIME)
{
}


SlamAIComponent::~SlamAIComponent()
{
}

void SlamAIComponent::start(Scene & scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	health_ = owner_.getComponent<HealthComponent>();
	boss_ = owner_.getComponent<BossAIComponent>();
}

void SlamAIComponent::update(Scene & scene)
{
	if (attack_initiated_)
	{
		timer_ += Time::getElapsedUpdateTimeSeconds();
		if (timer_ > windup_time_ + swing_time_ + lag_time_)
		{
			claw_->kill();
			attack_initiated_ = false;
			timer_ = 0;
			boss_->setAttack("Idle");
		}
		else if (timer_ > swing_time_ + windup_time_)
		{
			claw_physics_->setVelX(boss_->getFacing() * SPEED * windup_speed_);

		}
		else if (timer_ > swing_time_)
		{
			claw_physics_->setVelX(boss_->getFacing() * SPEED * swing_speed_);
		}

	}

	else
	{
		attack_initiated_ = true;
		claw_ = scene.gameObjects.add("EnemyProjectile", "ClawProjectile", owner_.getPos() + Point(0, 18));
		claw_physics_ = claw_->getComponent<PhysicsComponent>();
		claw_physics_->setVelX(windup_speed_ * 60.0f);

	}
}