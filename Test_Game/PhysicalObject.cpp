#include "PhysicalObject.h"


PhysicalObject::PhysicalObject()
	:velX(0), velY(0), accelX(0), accelY(0), falling(true)
{
}


PhysicalObject::~PhysicalObject()
{
}

int PhysicalObject::getVelX()
{
	return velX;
}

int PhysicalObject::getVelY()
{
	return velY;
}

int PhysicalObject::getAccelX()
{
	return accelX;
}

int PhysicalObject::getAccelY()
{
	return accelY;		
}

bool PhysicalObject::isMovingUp()
{
	return velY < 0;
}

bool PhysicalObject::isMovingDown()
{
	return velY > 0;
}

bool PhysicalObject::isMovingLeft()
{
	return velX < 0;
}

bool PhysicalObject::isMovingRight()
{
	return velX > 0;
}

void PhysicalObject::toggleGravity(bool gravity)
{
	gravityEnabled = gravity; 
}

void PhysicalObject::fall()
{
	if (gravityEnabled && falling)
	{
		velY += GRAVITY;
		if (velY > TERMINAL_VELOCITY)
			velY = TERMINAL_VELOCITY;
	}
}

void PhysicalObject::moveX()
{
	velX += accelX; 
	position.x += velX;
}

void PhysicalObject::moveY()
{
	fall();
	velY += accelY;
	position.y += velY;
}
