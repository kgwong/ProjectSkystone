#ifndef POINT_H
#define POINT_H
#include <iostream>

struct Point
{
	Point();
	Point(float posX, float posY);
	Point(int posX, int posY);

	Point operator+(const Point& rhs) const;
	Point operator-(const Point& rhs) const;
	bool operator==(const Point& rhs) const;
	bool operator!=(const Point& rhs) const;
	bool inBounds(float levelWidth, float levelHeight);

	bool inGameObject(Point pt, float height, float width);

	float x;
	float y;

	static float getDistance(Point& a, Point& b);
	static float getXDistance(Point& a, Point& b);
	static float getYDistance(Point& a, Point& b);
	static float getXDirection(Point& a, Point& b);
	static float getYDirection(Point& a, Point& b);
	static bool sameDistance(Point& a, Point& b, float dist);
	static Point getMidPoint(Point& a, Point& b);
	static float getXMidPoint(Point& a, Point& b);
	static float getYMidPoint(Point& a, Point &b);
	static float getFacingDirection(Point&a, Point&b);
};

std::ostream& operator<<(std::ostream& out, const Point& f);

#endif //POINT_H