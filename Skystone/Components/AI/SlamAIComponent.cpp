#include "SlamAIComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Common/HealthComponent.h"
#include "Game/GameTime.h"


SlamAIComponent::SlamAIComponent(GameObject & owner) :
	AIComponent(owner),
	attack_initiated_(false),
	timer_(0),
	windup_time_(DEFAULT_WINDUP_TIME),
	windup_speed_(DEFAULT_WINDUP_SPEED)
{
}


SlamAIComponent::~SlamAIComponent()
{
}

void SlamAIComponent::start(Scene & scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	health_ = owner_.getComponent<HealthComponent>();
}

void SlamAIComponent::update(Scene & scene)
{
	if (attack_initiated_)
	{
		timer_ += Time::getElapsedUpdateTimeSeconds();
		if (timer_ > windup_time_)
		{
			
		}
	}

	else
	{
		attack_initiated_ = true;
		auto attack = scene.gameObjects.add("EnemyProjectile", "ClawProjectile", owner_.getPos() + Point(0, 18));
		auto physics = attack->getComponent<PhysicsComponent>();
		physics->setVelX(windup_speed_ * 60.0f);


	}
}