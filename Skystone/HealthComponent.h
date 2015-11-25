#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"

class HealthComponent : public Component
{
public:
	static const int DEFAULT_HEALTH = 100;
	static const int DEFAULT_INVINCIBILITY_TIME = 100;

public:
	HealthComponent();
	HealthComponent(int initHealth);
	virtual ~HealthComponent();

	virtual void start(GameObject& owner, Level& level) {};
	virtual void update(GameObject& owner, Level& level);

	void setInvincibilityTime(int time);
	void setInvincible(bool value);

	bool takeDamage(int damage);
	bool heal(int addedHealth);

	int getHealth();
	bool isDead();

private:
	int health_; 
	bool invincible_;

	int invincibilityTime_;
	int remainingInvincibilityTime_;

};


#endif //HEALTHCOMPONENT_H