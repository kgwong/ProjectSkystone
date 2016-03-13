#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Components/UpdatingComponent.h"

class HealthComponent : public UpdatingComponent
{
public:
	static const int DEFAULT_HEALTH = 100;
	static const int DEFAULT_INVINCIBILITY_TIME = 100;

public:
	HealthComponent(GameObject& owner);
	HealthComponent(GameObject& owner, int initHealth);
	virtual ~HealthComponent();

	virtual void start(Scene& scene) {};
	virtual void update(Scene& scene);

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