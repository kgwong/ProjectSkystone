#include "TrackerComponent.h"

#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Level.h"

//all AICOMPONENTS get called in EnemyBuilder.cpp

//finished by Harvey and Aaron! :)

TrackerComponent::TrackerComponent()
	:xVelocity_(DEFAULT_X_VELOCITY),
	radius_(DEFAULT_RADIUS), enemyState_(EnemyState::FOLLOWER)
{
}


TrackerComponent::~TrackerComponent()
{
}

void TrackerComponent::start(GameObject & owner, Level & level)
{
	physics_ = owner.getComponent<PhysicsComponent>();

}


//missing time and another player gameobject.
void TrackerComponent::update(GameObject & owner, Level & level)
{
	int player_dist = AIComponent::getDistance(owner.getPos(), level.getPlayerPos());
	
	
	if (enemyState_ == EnemyState::FOLLOWER)
	{
		if (AIComponent::isNearby(player_dist, radius_))
		{
			xVelocity_ = RUNNING_X_VELOCITY;
			int player_direction = AIComponent::getXDirection(owner.getPos(), level.getPlayerPos());
			//if player is to left of enemy
			if (player_direction < 0)
				physics_->setVelX(xVelocity_);
			else//if player is to right of enemy
				physics_->setVelX(-xVelocity_);
		}
		else
		{
			xVelocity_ = DEFAULT_X_VELOCITY;
			physics_->setVelX(xVelocity_);
		}
	}
	else if (enemyState_ == EnemyState::COWARD)
	{
		if (AIComponent::isNearby(player_dist, radius_))
		{
			xVelocity_ = RUNNING_X_VELOCITY;
			int player_direction = AIComponent::getXDirection(owner.getPos(), level.getPlayerPos());
			//if player is to left of enemy
			if (player_direction < 0)
				physics_->setVelX(-xVelocity_);
			else//if player is to right of enemy
				physics_->setVelX(xVelocity_);
		}
		else
		{
			xVelocity_ = DEFAULT_X_VELOCITY;
			physics_->setVelX(xVelocity_);
		}
	}

	
	
}

EnemyState TrackerComponent::getEnemyState()
{
	return enemyState_;
}
