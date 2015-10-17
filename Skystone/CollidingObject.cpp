#include "CollidingObject.h"

CollidingObject::CollidingObject()
{
}

CollidingObject::~CollidingObject()
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

/*

//belongs with code that handles collision.... probably not here!
void CollidingObject::resolveEnvironmentCollision(LevelEntities& entities, Axis axis)
{
	//will throw std::out_of_range if player goes off screen!
	for (int x = position.x/entities.tileSize; x <= (position.x + width)/entities.tileSize; ++x)
	{
		for(int y = position.y/entities.tileSize; y <= (position.y + height)/entities.tileSize; ++y)
		{
			Tile& tile = entities.tiles[y][x];
			if(tile.tileType == 1 && checkCollision(dynamic_cast<CollidingObject &>(tile))
			{
				switch(axis)
				{
					case X: handleCollisionX(tile); break;
					case Y: handleCollisionY(tile); break;
				}
			}
		}
	}

}

void resolveCollisionX(const CollidingObject& other)
{
	if (isMovingLeft())
		position.x = other.getPosX() + other.getWidth();
	else //isMovingRight
		position.x = other.getPosX() - width;
}

void resolveCollisionY(const CollidingObject& other)
{

}*/

