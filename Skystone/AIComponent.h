#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "Component.h"
#include "Point.h"

class AIComponent : public Component
{
public:
	AIComponent(GameObject& owner)
		:Component(owner)
	{

	}
	virtual ~AIComponent() {};

	virtual void start(Level& level) = 0;
	virtual void update(Level& level) = 0;

	virtual void handleEvent(const CollisionEvent& e);
	virtual void handleEvent(const ComponentEvent& e);

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