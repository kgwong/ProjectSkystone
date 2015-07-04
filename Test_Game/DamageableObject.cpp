#include "DamageableObject.h"


DamageableObject::DamageableObject()
	:health(100)
{
}


DamageableObject::~DamageableObject()
{
}

void DamageableObject::takeDamage(int damage)
{
	health -= damage;
}

void DamageableObject::heal(int addedHealth)
{
	health += addedHealth;
}

bool DamageableObject::isDead()
{
	return health <= 0;
}
