#include "AlligatorAIComponent.h"
#include "GameTypes/Point.h"
#include "Game/GameTime.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"


using namespace std;


AlligatorAIComponent::AlligatorAIComponent(GameObject & owner)
	:AIComponent(owner),
	short_walk_(DEFAULT_SHORT_WALK),
	long_walk_(DEFAULT_LONG_WALK),
	move_speed_(DEFAULT_MOVE_SPEED),
	action_time_(DEFAULT_ACTION_TIME),
	moving_(false),
	move_time_(0),
	timer_(0),
	move_timer_(0)

	
{
}

//every 4 seconds (action_time_), pick a new action based on main timer
//if short_walk_, walk for a certain timer, then wait for main timer 
//if long_walk_, do the same except walk further before waiting
//pick direction, if 0, do nothing for duration of timer

AlligatorAIComponent::~AlligatorAIComponent()
{
}

void AlligatorAIComponent::start(Scene & scene)
{
	select_action_[0] = short_walk_;
	select_action_[1] = long_walk_;
	physics_ = owner_.getComponent<PhysicsComponent>();

}

void AlligatorAIComponent::update(Scene & scene)
{
	timer_ += Time::getElapsedUpdateTimeSeconds();
	if (timer_ > action_time_)
	{
		int generate_action = rand() % 3;
		int generate_direction = rand() % 3 - 1;
		physics_->setVelX(60.0f * move_speed_ * generate_direction);
		moving_ = true;
		move_time_ = select_action_[generate_action];
		timer_ = 0;

	}

	if (moving_)
	{
		move_timer_ += Time::getElapsedUpdateTimeSeconds();
		if (move_timer_ > move_time_)
		{
			physics_->setVelX(0);
			move_timer_ = 0;
			moving_ = false;
		}
	}
}