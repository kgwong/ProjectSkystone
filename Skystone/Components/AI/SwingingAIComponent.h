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
	virtual void start(Scene& scene);
	virtual void update(Scene& scene);
	virtual void handleEvent(const CollisionEvent& e);
private:
	PhysicsComponent * physics_;
	float radius_;//rope length = original - current position.
	float stepRadius_;//how much the length of the rope can change by.
	Point center_;//pivot point

	Point originalPosition_;//equilibrium point
	Point currentPosition_;

	float maxAngle_;//max theta
	float currentAngle_;//current theta
	float angleVelocity_;//angular velocity ~ can change to float
	int direction_;
	bool isHit_;
	float timer_;//change to float later.


	float swingTime_;//period of oscilation, time it takes for one full swing.
	float damp;//air friciton.
};

#endif //SWINGING_AI_COMPONENT

