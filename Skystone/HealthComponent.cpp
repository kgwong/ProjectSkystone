#include "HealthComponent.h"


HealthComponent::HealthComponent()
	:_health(100)
{
}

HealthComponent::HealthComponent(int initHealth)
	:_health(initHealth)
{

}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::takeDamage(int damage)
{
	_health -= damage;
}

void HealthComponent::heal(int addedHealth)
{
	_health += addedHealth;
}
	
int HealthComponent::getHealth()
{
	return _health;
}

bool HealthComponent::isDead()
{
	return _health <= 0;
}