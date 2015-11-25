#include "HealthComponent.h"

#include <iostream> //

HealthComponent::HealthComponent()
	:health_(DEFAULT_HEALTH),
	invincible_(false),
	invincibilityTime_(DEFAULT_INVINCIBILITY_TIME),
	remainingInvincibilityTime_(0)
{
}

HealthComponent::HealthComponent(int initHealth)
	:health_(initHealth),
	invincible_(false),
	invincibilityTime_(DEFAULT_INVINCIBILITY_TIME),
	remainingInvincibilityTime_(0)
{

}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::update(GameObject& owner, Level& level)
{
	if (remainingInvincibilityTime_ <= 0)
	{
		invincible_ = false;;
	}
	else
	{
		remainingInvincibilityTime_--;
		//std::cout << "Invincible " << remainingInvincibilityTime_ << std::endl;
	}
}

void HealthComponent::setInvincibilityTime(int time)
{
	invincibilityTime_ = time;
}

void HealthComponent::setInvincible(bool value)
{
	invincible_ = value;
	if (value == true)
	{
		remainingInvincibilityTime_ = invincibilityTime_;
	}
}

bool HealthComponent::takeDamage(int damage)
{
	if (!invincible_)
	{
		health_ -= damage;
		return true;
	}
	return false;
}

bool HealthComponent::heal(int addedHealth)
{
	health_ += addedHealth;
	return true;
}
	
int HealthComponent::getHealth()
{
	return health_;
}

bool HealthComponent::isDead()
{
	return health_ <= 0;
}