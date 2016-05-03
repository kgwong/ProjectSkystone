#include "HealthComponent.h"

#include <iostream> //

HealthComponent::HealthComponent(GameObject& owner)
	: HealthComponent(owner, DEFAULT_HEALTH)
{
}

HealthComponent::HealthComponent(GameObject& owner, int initHealth)
	: UpdatingComponent(owner),
	currentHealth_(initHealth),
	maxHealth_(initHealth),
	invincible_(false),
	invincibilityTime_(DEFAULT_INVINCIBILITY_TIME),
	remainingInvincibilityTime_(0)
{

}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::update(Scene& scene)
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

	if (currentHealth_ <= 0)
	{
		owner_.kill();
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
		currentHealth_ -= damage;
		return true;
	}
	return false;
}

bool HealthComponent::heal(int addedHealth)
{
	if (currentHealth_ == maxHealth_)
		return false;

	if(currentHealth_ + addedHealth <= maxHealth_)
		currentHealth_ += addedHealth;
	else
		currentHealth_ = maxHealth_;
	return true;
}
	
int HealthComponent::getHealth()
{
	return currentHealth_;
}

int HealthComponent::getMaxHealth()
{
	return maxHealth_;
}

bool HealthComponent::isDead()
{
	return currentHealth_ <= 0;
}