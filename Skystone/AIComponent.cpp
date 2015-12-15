#include "AIComponent.h"

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

int AIComponent::getYDirection(Point & a, Point & b)
{
	return a.y - b.y;
}

bool AIComponent::isNearby(int dist,int radius)
{
	return std::abs(dist) <= radius;
}


Point AIComponent::getMidPoint(Point& a, Point& b)
{
	int midX = abs(a.x + b.x) / 2;
	int midY = abs(a.y + b.y) / 2;

	return Point{ midX, midY };
}
int AIComponent::getXMidPoint(Point& a, Point& b)
{
	return abs(a.x + b.x) / 2;
}
int AIComponent::getYMidPoint(Point& a, Point &b)
{
	return abs(a.y + b.y) / 2;
}
