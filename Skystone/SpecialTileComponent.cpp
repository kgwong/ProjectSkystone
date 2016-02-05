#include "SpecialTileComponent.h"
#include "PhysicsComponent.h"



SpecialTileComponent::SpecialTileComponent(GameObject & owner):
	UpdatingComponent(owner)
{
}


SpecialTileComponent::~SpecialTileComponent()
{
}

int SpecialTileComponent::getDistance(Point& a, Point& b)
{
	int x2 = a.x;
	int x1 = b.x;
	int y2 = a.y;
	int y1 = b.y;
	int dist = (int)sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist;
}

int SpecialTileComponent::getXDirection(Point & a, Point & b)
{
	return a.x - b.x;
}

int SpecialTileComponent::getYDirection(Point & a, Point & b)
{
	return a.y - b.y;
}

bool SpecialTileComponent::isNearby(int dist, int radius)
{
	return std::abs(dist) <= radius;
}
