#ifndef COLLIDINGOBJECT_H
#define COLLIDINGOBJECT_H

#include "GameObject.h"

class CollidingObject : public virtual GameObject //diamond structure oops?
{
public:
	CollidingObject();
	~CollidingObject();

	bool checkCollision(const CollidingObject& other);
	
protected:

	/*void resolveEnvironmentCollision(LevelEntities& entities, Axis axis)
	void resolveCollisionX(const CollidingObject& other);
	void resolveCollisionY(const CollidingObject& other);*/
};


#endif //COLLIDINGOBJECT_H