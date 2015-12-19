#ifndef SWINGING_AI_COMPONENT
#define SWINGING_AI_COMPONENT

#include "AIComponent.h"

class PhysicsComponent;


static bool onHit = false;

class SwingingAIComponent :
	public AIComponent
{
public:
	static const int DEFAULT_MIN_ANGLE = -80;
	static const int DEFAULT_MAX_ANGLE = 80;
	static const int ANGULAR_VELOCITY = 3;
public:
	SwingingAIComponent(GameObject& owner);
	virtual ~SwingingAIComponent();
	virtual void start(Level& level);
	virtual void update(Level& level);
private:
	PhysicsComponent * physics_;
	int radius_;//rope length
	int stepRadius_;//how much the length of the rope can change by.
	Point center_;

	Point originalPosition_;
	Point currentPosition_;

	int minAngle_, maxAngle_;
	int currentAngle_;
	int angleVelocity_;
	int direction_;
};

#endif //SWINGING_AI_COMPONENT

