#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "GameObject.h"

//A PhysicalObject is a GameObject that moves and is affected by gravity

class PhysicalObject : public virtual GameObject
{
public:
	PhysicalObject();
	~PhysicalObject();

	int getVelX();
	int getVelY();
	int getAccelX();
	int getAccelY();

	bool isMovingUp();
	bool isMovingDown();
	bool isMovingLeft();
	bool isMovingRight();

	void toggleGravity(bool gravity);

protected:
	static const int GRAVITY = 1;
	static const int TERMINAL_VELOCITY = 20;

	int velX, velY;
	int accelX, accelY;

	bool gravityEnabled; //gravity enabled?
	bool falling; //object is falling

protected:
	void fall();
	void move();
	void moveX();
	void moveY();
};


#endif //PHYSICALOBJECT_H
