#ifndef FALLING_AI_COMPONENT_H
#define FALLING_AI_COMPONENT_H
#include "AIComponent.h"

class PhysicsComponent;

class FallingAIComponent :
	public AIComponent
{


public:
	static const int DEFAULT_Y_VELOCITY = 0;
	static const int DEFAULT_RISE_VELOCITY = -3;
	static const int DEFAULT_X_RADIUS = 25;
	static const int DEFAULT_Y_RADIUS = 100;
	static const int DEFAULT_TIME_INTERVAL = 100;

public:
	FallingAIComponent(GameObject& owner);
	virtual ~FallingAIComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	int yVelocity_;
	int xRadius_;
	int yRadius_;
	PhysicsComponent* physics_;

	int timer_;
	bool isFalling_;
};

#endif