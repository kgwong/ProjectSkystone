#ifndef SWINGING_AI_COMPONENT
#define SWINGING_AI_COMPONENT

#include "AIComponent.h"

class PhysicsComponent;


class SwingingAIComponent :
	public AIComponent
{
public:
	static const int DEFAULT_MIN_ANGLE = -80;
	static const int DEFAULT_MAX_ANGLE = 80;
	static const int ANGULAR_VELOCITY = 2;
	static const int TIME_TO_SWING = 180;//may delete in the future
public:
	SwingingAIComponent(GameObject& owner);
	virtual ~SwingingAIComponent();
	virtual void start(Level& level);
	virtual void update(Level& level);
	virtual void handleEvent(const CollisionEvent& e);
private:
	PhysicsComponent * physics_;
	int radius_;//rope length = original - current position.
	int stepRadius_;//how much the length of the rope can change by.
	Point center_;//pivot point

	Point originalPosition_;//equilibrium point
	Point currentPosition_;

	int maxAngle_;//max theta
	int currentAngle_;//current theta
	float angleVelocity_;//angular velocity ~ can change to float
	int direction_;
	bool isHit_;
	float timer_;//change to float later.


	float swingTime_;//period of oscilation, time it takes for one full swing.
};

#endif //SWINGING_AI_COMPONENT

