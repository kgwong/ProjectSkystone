#ifndef COLLIDINGOBJECT_H
#define COLLIDINGOBJECT_H

#include "GameObject.h"

class CollidingObject : public virtual GameObject //diamond structure oops?
{
public:
	CollidingObject();
	~CollidingObject();

	bool checkCollision(const CollidingObject& other);

};


#endif //COLLIDINGOBJECT_H