#ifndef POINT_H
#define POINT_H

struct Point
{
	Point(): x(0), y(0) {}
	Point(int x, int y): x(x), y(y) {} 
	int x;
	int y;
};

#endif //POINT_H