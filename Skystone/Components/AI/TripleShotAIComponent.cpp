#include "TripleShotAIComponent.h"
#include "Game/GameTime.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"
#include "BossAIComponent.h"
#define SPEED 60.0f


TripleShotAIComponent::TripleShotAIComponent(GameObject& owner, std::string enemy_type) :
	AIComponent(owner),
	delay_(DEFAULT_PROJECTILE_DELAY),
	timer_(0),
	enemy_type_(enemy_type),
	projectile_speed_(DEFAULT_PROJECTILE_SPEED),
	cooldown_(false),
	firing_(true),
	projectile_count_(DEFAULT_PROJECTILE_COUNT),
	current_count_(0),
	cooldown_time_(DEFAULT_COOLDOWN_TIME),
	xDist(0),
	yDist(0),
	playerSide(0)
{
}


TripleShotAIComponent::~TripleShotAIComponent()
{
}

void TripleShotAIComponent::start(Scene& scene)
{
	boss_ = owner_.getComponent<BossAIComponent>();

}

void TripleShotAIComponent::update(Scene& scene)
{

		timer_ += Time::getElapsedUpdateTimeSeconds();
			if (timer_ > delay_)
			{	
				if (current_count_ == 0)
				{
					xDist = Point::getXDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
					playerSide = Point::getFacingDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
					yDist = Point::getYDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
				}
				fireProjectileDirection(xDist, yDist, playerSide, 3, scene, projectile_speed_);
				fireProjectileDirection(xDist, yDist, playerSide, 0, scene, projectile_speed_);
				fireProjectileDirection(xDist, yDist, playerSide, -3, scene, projectile_speed_);
				current_count_++;
				timer_ = 0;
				if (current_count_ >= projectile_count_)
				{
					current_count_ = 0;
					boss_->setAttack("Idle");
				}
			}
		

	}
//}

