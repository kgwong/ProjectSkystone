#ifndef POINT_H
#define POINT_H

struct Point
{
	//should probably update C++ version hahaha...
	Point(): x(0), y(0) {}
	Point(int x, int y): x(x), y(y) {} 
	int x /*= 0*/;
	int y /*= 0*/;
};

#endif //POINT_H