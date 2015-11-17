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
	static const int DEFAULT_RADIUS = 150;

public:
	FallingAIComponent();
	virtual ~FallingAIComponent();

	virtual void start(GameObject& owner, Level& level);
	virtual void update(GameObject& owner, Level& level);


private:
	int yVelocity_;
	int radius_;
	PhysicsComponent* physics_;

	int timer_;
	bool isFalling_;
};

#endif