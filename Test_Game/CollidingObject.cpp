#include "CollidingObject.h"

CollidingObject::CollidingObject(void)
{
}


CollidingObject::~CollidingObject(void)
{
}

bool CollidingObject::checkCollision(const CollidingObject& other)
{

	int topOther = other.position.y;
	int topSelf = position.y; 

	int bottomOther = other.position.y + other.height;
	int bottomSelf = position.y + height; 

	int leftOther = other.position.x;
	int leftSelf = position.x; 

	int rightOther = other.position.x + other.width;
	int rightSelf = position.x + width; 

	if (topSelf >= bottomOther)
		return false;
	if (bottomSelf <= topOther)
		return false;
	if (leftSelf >= rightOther)
		return false;
	if (rightSelf <= leftOther)
		return false;

	return true;
}

