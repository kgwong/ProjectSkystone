#include "AIComponent.h"
#include "GameObject.h"


int AIComponent::getDistance(Point& a,Point& b)
{
	int x2 = a.x;
	int x1 = b.x;
	int y2 = a.y;
	int y1 = b.y;
	int dist = (int)sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );


	return dist;
}

int AIComponent::getXDirection(Point & a, Point & b)
{
	return a.x - b.x;
}

bool AIComponent::isNearby(int dist,int radius)
{
	return std::abs(dist) <= radius;
}
int AIComponent::getYDirection(Point & a, Point & b)
{
	return a.y - b.y;
}
