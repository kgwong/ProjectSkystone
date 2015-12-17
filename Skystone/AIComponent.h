#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "Component.h"
#include "Point.h"

class AIComponent : public Component
{
public:
	virtual ~AIComponent() {};

	virtual void start(GameObject& owner, Level& level) {};
	virtual void update(GameObject& owner, Level& level) {};



	static int getDistance(Point& a,Point& b);
	static int getXDistance(Point& a, Point& b);
	static int getYDistance(Point& a, Point& b);
	static int getXDirection(Point& a, Point& b);
	static int getYDirection(Point& a, Point& b);
	static bool isNearby(int dist, int radius);
	static bool isDistance(Point& a, Point& b, int dist);

	static Point getMidPoint(Point& a, Point& b);
	static int getXMidPoint(Point& a, Point& b);
	static int getYMidPoint(Point& a, Point &b);
};

#endif //AI_COMPONENT_H