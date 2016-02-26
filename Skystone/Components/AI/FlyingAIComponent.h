#ifndef FLYING_AI_COMPONENT_H
#define FLYING_AI_COMPONENT_H
#include "AIComponent.h"

class PhysicsComponent;

class FlyingAIComponent :
	public AIComponent
{


public:
	static const int DEFAULT_X_DIRECTION_TIME = 72; //use Time::
	static const int DEFAULT_Y_DIRECTION_CHANGES = 6;
	static const float DEFAULT_X_VELOCITY;
	static const float DEFAULT_Y_VELOCITY;

public:
	FlyingAIComponent(GameObject& owner);
	virtual ~FlyingAIComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	float xVelocity_, yVelocity_;
	PhysicsComponent* physics_;
	int timeInterval_;
};

#endif 