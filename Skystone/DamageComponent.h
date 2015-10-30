#ifndef DAMAGECOMPONENT_H
#define DAMAGECOMPONENT_H

#include "Component.h"

class DamageComponent :	public Component
{
public:
	DamageComponent();
	DamageComponent(int damage);
	virtual ~DamageComponent();

	virtual void start(GameObject& owner, Level& level) {};
	virtual void update(GameObject& owner, Level& level) {};

	int getDamage();

private:
	int _damage;
};

#endif //DAMAGECOMPONENT_H

