#include "DamageComponent.h"

DamageComponent::DamageComponent()
	: _damage(0)
{

}

DamageComponent::DamageComponent(int damage)
	: _damage(damage)
{
}


DamageComponent::~DamageComponent()
{
}


int DamageComponent::getDamage()
{
	return _damage;
}