#include "TripleShotAIComponent.h"
#include "Game/GameTime.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"
#define SPEED 60.0f


TripleShotAIComponent::TripleShotAIComponent(GameObject& owner, std::string enemy_type) :
	AIComponent(owner),
	delay_(DEFAULT_PROJECTILE_DELAY),
	timer_(0),
	enemy_type_(enemy_type),
	projectile_speed_(DEFAULT_PROJECTILE_SPEED),
	cooldown_(false),
	firing_(false),
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

}

void TripleShotAIComponent::update(Scene& scene)
{

	if (!cooldown_)
	{
		xDist = Point::getXDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
		playerSide = Point::getFacingDirection(xDist, owner_.getPos(), scene.gameObjects.getPlayer().getPos());
		yDist = Point::getYDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
		fireProjectile(xDist, yDist, playerSide, 3, scene);
		fireProjectile(xDist, yDist, playerSide, 0, scene);
		fireProjectile(xDist, yDist, playerSide, -3, scene);
		cooldown_ = true;
		firing_ = true;
		current_count_++;
	}
	
	else
	{
		timer_ += Time::getElapsedUpdateTimeSeconds();
		if (firing_)
		{
			if (timer_ > delay_)
			{
				fireProjectile(xDist, yDist, playerSide, 3, scene);
				fireProjectile(xDist, yDist, playerSide, 0, scene);
				fireProjectile(xDist, yDist, playerSide, -3, scene);
				current_count_++;
				timer_ = 0;
				if (current_count_ >= projectile_count_)
				{
					firing_ = false;
					current_count_ = 0;
				}
			}
		}
		else if (timer_ > cooldown_time_)
		{
			timer_ = 0;
			cooldown_ = false;
		}

	}
}

void TripleShotAIComponent::fireProjectile(float xDist, float yDist, float playerSide, float offset, Scene& scene)
{
	auto bullet = scene.gameObjects.add("EnemyProjectile", "AcidProjectile", owner_.getPos() + Point(0, 25));
	auto bullet_physics = bullet->getComponent<PhysicsComponent>();
	float newVelX = projectile_speed_ * playerSide;
	bullet_physics->setVelX(newVelX * SPEED);
	bullet_physics->setVelY((newVelX * yDist  / xDist + offset) * SPEED);
}