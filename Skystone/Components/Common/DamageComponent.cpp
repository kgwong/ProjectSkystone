#include "DamageComponent.h"

DamageComponent::DamageComponent(GameObject& owner)
	: NonUpdatingComponent(owner),
	_damage(0)
{

}

DamageComponent::DamageComponent(GameObject& owner, int damage)
	: NonUpdatingComponent(owner),
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