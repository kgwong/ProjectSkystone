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
	const static float DEFAULT_RADIUS;
	const static double DEFAULT_COOLDOWN_TIME;


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