#include "DamageComponent.h"

#include <iostream>

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

void* DamageComponent::getAttribute(const std::string& name)
{
	if (name == "damage")
	{
		return &_damage;
	}
	return nullptr; //should probably throw an exception
}
