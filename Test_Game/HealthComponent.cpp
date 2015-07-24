#include "HealthComponent.h"


HealthComponent::HealthComponent()
	:_health(100)
{
}


HealthComponent::~HealthComponent()
{
}

void HealthComponent::update(GameObject& owner)
{

}

void HealthComponent::initHealth(int health)
{
	_health = health;
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