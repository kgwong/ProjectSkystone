#ifndef FALLING_AI_COMPONENT_H
#define FALLING_AI_COMPONENT_H
#include "AIComponent.h"

class PhysicsComponent;

class FallingAIComponent :
	public AIComponent
{


public:
	static const float DEFAULT_Y_VELOCITY;
	static const float DEFAULT_RISE_VELOCITY;
	static const float DEFAULT_X_RADIUS;
	static const float DEFAULT_Y_RADIUS;
	static const int DEFAULT_TIME_INTERVAL = 100;

public:
	FallingAIComponent(GameObject& owner);
	virtual ~FallingAIComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	float yVelocity_;
	float xRadius_;
	float yRadius_;
	PhysicsComponent* physics_;

	int timer_;
	bool isFalling_;
};

#endif