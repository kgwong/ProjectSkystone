#ifndef FLYING_AI_COMPONENT_H
#define FLYING_AI_COMPONENT_H
#include "AIComponent.h"
#include "Game/GameTime.h"

class PhysicsComponent;

class FlyingAIComponent :
	public AIComponent
{


public:
	static const float DEFAULT_X_DIRECTION_CHANGE; //use Time::
	static const float DEFAULT_Y_DIRECTION_CHANGE; 
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
	float xchange_;
	float ychange_;

};

#endif 