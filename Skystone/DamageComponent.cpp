#include "DamageComponent.h"

DamageComponent::DamageComponent(GameObject& owner)
	: Component(owner), 
	_damage(0)
{

}

DamageComponent::DamageComponent(GameObject& owner, int damage)
	: Component(owner),
	_damage(damage)
{
}


DamageComponent::~DamageComponent()
{
}


int DamageComponent::getDamage()
{
	return _damage;
}