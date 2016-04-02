#ifndef POUNCE_AI_COMPONENT_H
#define POUNCE_AI_COMPONENT_H

#include "AIComponent.h"

class PhysicsComponent;
class ColliderComponent;

class PounceAIComponent :
	public AIComponent
{

public:
	//use Time::
	const float DEFAULT_JUMP_HEIGHT = -10;
	const float DEFAULT_JUMP_DISTANCE = 7;
	const float DEFAULT_RADIUS = 175.0f;
	const double PounceAIComponent::DEFAULT_COOLDOWN_TIME = 1.5;


public:
	PounceAIComponent(GameObject& owner);
	virtual ~PounceAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	PhysicsComponent* physics_;
	float radius_;
	double timer_;
	double cooldown_time_;
	bool cooldown_;

};


#endif