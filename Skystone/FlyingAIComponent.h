#ifndef FLYING_AI_COMPONENT_H
#define FLYING_AI_COMPONENT_H
#include "AIComponent.h"

class PhysicsComponent;

class FlyingAIComponent :
	public AIComponent
{


public:
	static const int DEFAULT_X_DIRECTION_TIME = 72;
	static const int DEFAULT_Y_DIRECTION_CHANGES = 6;
	static const int DEFAULT_X_VELOCITY = 3;
	static const int DEFAULT_Y_VELOCITY = -1;

public:
	FlyingAIComponent(GameObject& owner);
	virtual ~FlyingAIComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	int xVelocity_;
	PhysicsComponent* physics_;
	int timeInterval_;
	int yVelocity_;


};

#endif 