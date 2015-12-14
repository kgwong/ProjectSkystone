#ifndef DAMAGECOMPONENT_H
#define DAMAGECOMPONENT_H

#include "Component.h"

class DamageComponent :	public Component
{
public:
	DamageComponent(GameObject& owner);
	DamageComponent(GameObject& owner, int damage);
	virtual ~DamageComponent();

	virtual void start(Level& level) {};
	virtual void update(Level& level) {};

	int getDamage();

private:
	int _damage;
};

#endif //DAMAGECOMPONENT_H

