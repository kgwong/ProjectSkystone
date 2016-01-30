#ifndef LIFT_COMPONENT_H
#define LIFT_COMPONENT_H

#include "Components/UpdatingComponent.h"
#include "Point.h"

class PhysicsComponent;

class LiftComponent : public UpdatingComponent
{
public:
	static const int DEFAULT_X_RADIUS = 25;
	static const int DEFAULT_DELAY = 7;


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

	int delay_;
	int time_;
	

};

#endif //#LIFT_COMPONENT_H