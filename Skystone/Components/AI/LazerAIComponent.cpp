#include "LazerAIComponent.h"
#include "BossAIComponent.h"
#include "GameTypes/Point.h"
#include "Game/GameTime.h"
#include "Application/Log.h"
#include "Components/Physics/PhysicsComponent.h"
#include <math.h>
#include "Components/Render/SpriteRenderer.h"
#include "Resources/Resources.h"
#define SPEED 60.0f

LazerAIComponent::LazerAIComponent(GameObject& owner, std::string enemyType) :
	AIComponent(owner),
	charge_time_(DEFAULT_CHARGE_TIME), 
	still_time_(DEFAULT_STILL_TIME),
	move_time_(DEFAULT_MOVE_TIME),
	timer_(0),
	start_(true),
	projectile_speed_(DEFAULT_PROJECTILE_SPEED),
	offset_(0),
	lazer_speed_(DEFAULT_LAZER_SPEED),
	enemy_type_(enemyType),
	xDist(0),
	yDist(0),
	playerSide(-1),
	firing_(false),
	Dist(0),
	projectile_delay_(DEFAULT_PROJECTILE_DELAY),
	delay_timer_(0)
{
}

LazerAIComponent::LazerAIComponent(GameObject& owner) :
	AIComponent(owner),
	charge_time_(DEFAULT_CHARGE_TIME),
	still_time_(DEFAULT_STILL_TIME),
	move_time_(DEFAULT_MOVE_TIME),
	timer_(0),
	start_(true),
	projectile_speed_(DEFAULT_PROJECTILE_SPEED),
	offset_(0),
	lazer_speed_(DEFAULT_LAZER_SPEED),
	enemy_type_(""),
	xDist(0),
	yDist(0),
	playerSide(-1),
	firing_(false),
	Dist(0),
	projectile_delay_(DEFAULT_PROJECTILE_DELAY),
	delay_timer_(0)
{
}


LazerAIComponent::~LazerAIComponent()
{
}


void LazerAIComponent::start(Scene& scene)
{
	boss_ = owner_.getComponent<BossAIComponent>();
}

void LazerAIComponent::update(Scene& scene)
{
	if (enemy_type_ == "Boss")
	{
		timer_ += Time::getElapsedUpdateTimeSeconds();

		if (start_)
		{
			start_ = false;
			charge_ = fireProjectile(0, 1, scene, 0, 0, -50);

		}

		else if (timer_ > charge_time_ && !firing_)
		{
			charge_->kill();
			firing_ = true;
			timer_ = 0;
			xDist = Point::getXDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
			playerSide = Point::getFacingDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
			yDist = Point::getYDirection(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
			Dist = Point::getDistance(owner_.getPos(), scene.gameObjects.getPlayer().getPos());
		}

		else if (firing_)
		{
			delay_timer_ += Time::getElapsedUpdateTime();
			if (delay_timer_ > projectile_delay_)
			{
				Resources::audioPlayer.PlayClip("laser1");
				fireProjectileDirection(xDist, yDist, playerSide, offset_, scene, projectile_speed_);
				delay_timer_ = 0;
			}
			if (timer_ < (move_time_ + still_time_) && timer_ > still_time_)
			{
				if (Point::getDistance(owner_.getPos(), scene.gameObjects.getPlayer().getPos()) < Dist)
				{
					offset_ += lazer_speed_;
				}
				else
				{
					offset_ -= lazer_speed_;
				}
			}
			else if (timer_ > (move_time_ + still_time_))
			{
				offset_ = 0;
				firing_ = false;
				start_ = true;
				timer_ = 0;
				boss_->setAttack("Idle");
			}
		}
	}
}
