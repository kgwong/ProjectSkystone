#include "Point.h"
#include <math.h>

Point::Point()
	:x(0), y(0)
{

}

Point::Point(int posX, int posY)
	:x(posX), y(posY)
{

}


Point Point::operator+(const Point & rhs) const
{
	return Point(this->x + rhs.x, this->y + rhs.y);
}

Point Point::operator-(const Point & rhs) const
{
	return Point(this->x - rhs.x, this->y - rhs.y);
}

bool Point::operator==(const Point & rhs) const
{
	return this->x == rhs.x && this->y == rhs.y;
}

int Point::getDistance(Point& a, Point& b)
{
	int x2 = a.x;
	int x1 = b.x;
	int y2 = a.y;
	int y1 = b.y;
	int dist = (int) sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist;
}

int Point::getXDistance(Point& a, Point& b)
{
	return abs(a.x - b.x);
}

int Point::getYDistance(Point& a, Point& b)
{
	return abs(a.y - b.y);
}

int Point::getXDirection(Point & a, Point & b)
{
	return a.x - b.x;
}

int Point::getYDirection(Point & a, Point & b)
{
	return a.y - b.y;
}

bool Point::isDistance(Point&a, Point&b, int dist)
{
	return getDistance(a, b) == dist;
}

Point Point::getMidPoint(Point& a, Point& b)
{
	int midX = abs(a.x + b.x) / 2;
	int midY = abs(a.y + b.y) / 2;

	return Point{ midX, midY };
}
int Point::getXMidPoint(Point& a, Point& b)
{
	return abs(a.x + b.x) / 2;
}
int Point::getYMidPoint(Point& a, Point &b)
{
	return abs(a.y + b.y) / 2;
}
