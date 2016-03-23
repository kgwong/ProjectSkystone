#include "Point.h"
#include <math.h>

Point::Point()
	:x(0), y(0)
{

}

Point::Point(float posX, float posY)
	:x(posX), y(posY)
{

}

Point::Point(int posX, int posY)
	:Point ((float)posX, (float)posY)
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

bool Point::operator!=(const Point & rhs) const
{
	return !(*this == rhs);
}

Point& Point::operator=(const Point & rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

float Point::getDistance(Point& a, Point& b)
{
	float x2 = a.x;
	float x1 = b.x;
	float y2 = a.y;
	float y1 = b.y;
	float dist = (float) sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist;
}

float Point::getXDistance(Point& a, Point& b)
{
	return fabsf(a.x - b.x);
}

float Point::getYDistance(Point& a, Point& b)
{
	return fabsf(a.y - b.y);
}

float Point::getXDirection(Point & a, Point & b)
{
	return a.x - b.x;
}

float Point::getYDirection(Point & a, Point & b)
{
	return a.y - b.y;
}

bool Point::isDistance(Point&a, Point&b, float dist)
{
	return getDistance(a, b) == dist;
}

Point Point::getMidPoint(Point& a, Point& b)
{
	float midX = fabsf(a.x + b.x) / 2;
	float midY = fabsf(a.y + b.y) / 2;

	return Point{ midX, midY };
}
float Point::getXMidPoint(Point& a, Point& b)
{
	return fabsf(a.x + b.x) / 2;
}
float Point::getYMidPoint(Point& a, Point &b)
{
	return fabsf(a.y + b.y) / 2;
}

std::ostream& operator<<(std::ostream& out, const Point& f)
{
	out << "(" << f.x << ", " << f.y << ")";
	return out;
}
