#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "Component.h"
#include "Point.h"

class AIComponent : public Component
{
public:
	AIComponent(GameObject& owner);
	virtual ~AIComponent();

	virtual void handleEvent(const CollisionEvent& e);
	virtual void handleEvent(const ComponentEvent& e);

	virtual Component::Type getType() final;

	static int getDistance(Point& a,Point& b);
	static int getXDirection(Point& a, Point& b);
	static bool isNearby(int dist, int radius);
	static int getYDirection(Point& a, Point& b);
};

#endif //AI_COMPONENT_H