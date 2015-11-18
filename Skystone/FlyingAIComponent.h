#ifndef FLYING_AI_COMPONENT_H
#define FLYING_AI_COMPONENT_H
#include "AIComponent.h"

class PhysicsComponent;

class FlyingAIComponent :
	public AIComponent
{


public:
	static const int DEFAULT_CHANGE_DIRECTION_TIME = 72;
	static const int DEFAULT_X_VELOCITY = 3;
	static const int DEFAULT_Y_VELOCITY = -1;

public:
	FlyingAIComponent();
	virtual ~FlyingAIComponent();

	virtual void start(GameObject& owner, Level& level);
	virtual void update(GameObject& owner, Level& level);

private:
	int xVelocity_;
	PhysicsComponent* physics_;
	int timer_;
	int timeInterval_;
	int yVelocity_;


};

#endif 