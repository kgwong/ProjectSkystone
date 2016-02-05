#ifndef SPECIAL_TILE_COMPONENT_H
#define SPECIAL_TILE_COMPONENT_H

#include "UpdatingComponent.h"
#include "Point.h"
#include "CollisionEvent.h"

class PhysicsComponent;

class SpecialTileComponent :
	public UpdatingComponent
{
public:
	SpecialTileComponent(GameObject& owner);
	virtual ~SpecialTileComponent();



	static int getDistance(Point& a, Point& b);
	static int getXDirection(Point& a, Point& b);
	static int getYDirection(Point& a, Point& b);
	static bool isNearby(int dist, int radius);
};

#endif //#SPECIAL_TILE_COMPONENT_H