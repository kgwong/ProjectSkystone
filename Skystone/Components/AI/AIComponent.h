#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "Components/Component.h"
#include "GameTypes/Point.h"

class AIComponent : public Component
{
public:
	AIComponent(GameObject& owner);
	virtual ~AIComponent();

	virtual void handleEvent(const CollisionEvent& e);
	virtual void handleEvent(const ComponentEvent& e);

	virtual Component::Type getType() final;

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