#include "TrackerComponent.h"

#include "Components/Physics/PhysicsComponent.h"

//all AICOMPONENTS get called in EnemyBuilder.cpp

//finished by Harvey and Aaron! :) 

const float TrackerComponent::DEFAULT_X_VELOCITY = 0 * 60.0f;
const float TrackerComponent::RUNNING_X_VELOCITY = 2 * 60.0f;
const float TrackerComponent::DEFAULT_RADIUS = 150.0f;

TrackerComponent::TrackerComponent(GameObject& owner)
	: AIComponent(owner),
	xVelocity_(DEFAULT_X_VELOCITY),
	radius_(DEFAULT_RADIUS),
	enemyState_(EnemyState::FOLLOWER)
{
}


TrackerComponent::~TrackerComponent()
{
}

void TrackerComponent::start(Level & level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
}


//missing time and another player gameobject.
void TrackerComponent::update(Level & level)
{
	float player_dist = Point::getDistance(owner_.getPos(), level.getPlayerPos());

	if (AIComponent::isNearby(player_dist, radius_))
	{
		float player_direction = Point::getXDirection(owner_.getPos(), level.getPlayerPos());

		EnemyState currentState = enemyState_;
			switch (currentState)
			{
			case EnemyState::FOLLOWER:
				followCommand((int)player_direction);
				break;
			case EnemyState::COWARD:
				fleeCommand((int)player_direction);
				break;
			case EnemyState::NEUTRAL:
				break;
			default:
				break;
			}
	}
	else
	{
		xVelocity_ = DEFAULT_X_VELOCITY;
		physics_->setVelX(xVelocity_);
	}
}

EnemyState TrackerComponent::getEnemyState()
{
	return enemyState_;
}

void TrackerComponent::setEnemyState(EnemyState state)
{
	enemyState_ = state;
}

void TrackerComponent::followCommand(int player_direction)
{
	xVelocity_ = RUNNING_X_VELOCITY;
	//if player is to left of enemy
	if (player_direction < 0)
		physics_->setVelX(xVelocity_);
	else//if player is to right of enemy
		physics_->setVelX(-xVelocity_);
}

void TrackerComponent::fleeCommand(int player_direction)
{
	xVelocity_ = RUNNING_X_VELOCITY;
	//if player is to left of enemy
	if (player_direction < 0)
		physics_->setVelX(-xVelocity_);
	else//if player is to right of enemy
		physics_->setVelX(xVelocity_);
}
