#ifndef DAMAGECOMPONENT_H
#define DAMAGECOMPONENT_H

#include "Components/NonUpdatingComponent.h"

class DamageComponent :	public NonUpdatingComponent
{
public:
	DamageComponent(GameObject& owner);
	DamageComponent(GameObject& owner, int damage);
	virtual ~DamageComponent();

	virtual void start(Scene& scene) {};

	int getDamage();

private:
	int _damage;
};

#endif //DAMAGECOMPONENT_H

