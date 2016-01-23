#ifndef LIFT_COMPONENT_H
#define LIFT_COMPONENT_H

#include "UpdatingComponent.h"
#include "Point.h"
#include "CollisionEvent.h"

class PhysicsComponent;

class LiftComponent : public UpdatingComponent
{
public:
	static const int DEFAULT_X_RADIUS = 25;


	LiftComponent(GameObject& owner);
	virtual ~LiftComponent();


	virtual void start(Level& level);
	virtual void update(Level& level);
	virtual void handleEvent(const CollisionEvent& other);

	static int getDistance(Point& a, Point& b);
	static int getXDirection(Point& a, Point& b);
	static int getYDirection(Point& a, Point& b);
	static bool isNearby(int dist, int radius);


private:
	PhysicsComponent* physics_;
	int xRadius_;

	int delay;
	

};

#endif //#LIFT_COMPONENT_H