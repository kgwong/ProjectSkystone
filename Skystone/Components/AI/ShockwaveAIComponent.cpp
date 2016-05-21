#include "ShockwaveAIComponent.h"
#include "Game/GameTime.h"
#include "BossAIComponent.h"
#include "../Collider/ColliderComponent.h"
#include "Application/Log.h"
#include "Resources/Resources.h"




ShockwaveAIComponent::ShockwaveAIComponent(GameObject& owner, std::string enemyType) :
	AIComponent(owner),
	shockwave_time_(DEFAULT_SHOCKWAVE_TIME),
	num_waves_(DEFAULT_NUM_WAVES),
	delay_(DEFAULT_DELAY),
	start_distance_(DEFAULT_STARTING_DISTANCE_X),
	timer_(0),
	enemy_type_(enemyType),
	distance_interval_(DEFAULT_DISTANCE_INTERVAL),
	projectile_speed_(DEFAULT_PROJECTILE_SPEED),
	facing_(-1),
	current_count_(0)
{
}


ShockwaveAIComponent::~ShockwaveAIComponent()
{
}

void ShockwaveAIComponent::start(Scene& scene)
{
	boss_ = owner_.getComponent<BossAIComponent>();
	collider_ = owner_.getComponent<ColliderComponent>();

	for (int i = 0; i < num_waves_; i++)
	{
		waves_.push_back(std::shared_ptr<GameObject>());
	}
}

void ShockwaveAIComponent::update(Scene& scene)
{
	timer_ += Time::getElapsedUpdateTimeSeconds();

	//FIND OUT WHICH DIRECTION ITS FACING; IMPLEMENT?////////////////////////////////////////
	if (enemy_type_ == "Boss")
	{
		facing_ = boss_->getFacing();
	}
	else
	{ //ONLY FOR MONSTERS THAT ALWAYS FACE THE PLAYER; ELSE, NEED IMPLEMENTATION
		float xDist = owner_.getPosX() - scene.gameObjects.getPlayer().getPosX();
		if (xDist < 0)
		{
			facing_ = 1;
		}
		else
		{
			facing_ = -1;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////
	if (timer_ > delay_)
	{
		Resources::audioPlayer.PlayClip("laser2");
		waves_[current_count_] = fireProjectile(0, -projectile_speed_, scene, 90, facing_ * start_distance_ + current_count_ * distance_interval_ * facing_, collider_->getBottom() - owner_.getPosY() - 10, "ClawProjectile");
		current_count_++;
		timer_ = 0;
		if (current_count_ >= num_waves_)
		{
			for (int i = 0; i < waves_.size(); i++)
			{
				waves_[i]->kill();
			}
			current_count_ = 0;
			if (enemy_type_ == "Boss")
			{
				boss_->setAttack("Idle");
			}
		}
	}
}