#ifndef DAMAGEABLEOBJECT_H
#define DAMAGEABLEOBJECT_H

#include "GameObject.h"

class DamageableObject : public virtual GameObject //diamond structure, oops?
{
public:
	DamageableObject();
	~DamageableObject();

	void takeDamage(int damage);
	void heal(int addedHealth);
	bool isDead();


private:
	int health;
};

#endif //DAMAGEABLEOBJECT_H
