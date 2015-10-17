#ifndef DAMAGECOMPONENT_H
#define DAMAGECOMPONENT_H

#include "Component.h"

class DamageComponent :	public Component
{
public:
	DamageComponent();
	DamageComponent(int damage);
	virtual ~DamageComponent();

	int getDamage();

private:
	int _damage;
};

#endif //DAMAGECOMPONENT_H

