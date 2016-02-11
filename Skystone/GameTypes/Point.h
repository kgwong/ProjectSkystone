#ifndef POINT_H
#define POINT_H

struct Point
{
	Point(): x(0), y(0) {}
	Point(int x, int y): x(x), y(y) {} 
	int x;
	int y;
	static int getDistance(Point& a, Point& b);
	static int getXDistance(Point& a, Point& b);
	static int getYDistance(Point& a, Point& b);
	static int getXDirection(Point& a, Point& b);
	static int getYDirection(Point& a, Point& b);
	static bool isDistance(Point& a, Point& b, int dist);
	static Point getMidPoint(Point& a, Point& b);
	static int getXMidPoint(Point& a, Point& b);
	static int getYMidPoint(Point& a, Point &b);

};

#endif //POINT_H