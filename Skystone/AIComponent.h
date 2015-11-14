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
	static int getXDirection(Point& a, Point& b);
	static bool isNearby(int dist, int radius);
};

#endif //AI_COMPONENT_H