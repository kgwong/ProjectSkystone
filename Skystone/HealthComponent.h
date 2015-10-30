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

	virtual void start(GameObject& owner, Level& level) {};
	virtual void update(GameObject& owner, Level& level) {};

	void takeDamage(int damage);
	void heal(int addedHealth);

	int getHealth();
	bool isDead();

private:
	int _health; 
};


#endif //HEALTHCOMPONENT_H