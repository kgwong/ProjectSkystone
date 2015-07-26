#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"
#include "GameObject.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	HealthComponent(int initHealth);
	virtual ~HealthComponent();

	virtual void update(GameObject& owner);

	void takeDamage(int damage);
	void heal(int addedHealth);

	int getHealth();
	bool isDead();

private:
	int _health; 
};


#endif //HEALTHCOMPONENT_H