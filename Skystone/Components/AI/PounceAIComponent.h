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
	const static int DEFAULT_COOLDOWN_TIME = 100;


public:
	PounceAIComponent(GameObject& owner);
	virtual ~PounceAIComponent();

	virtual void start(Level& level);
	virtual void update(Level& level);

private:
	PhysicsComponent* physics_;
	float radius_;
	int timeInterval_;
	int cooldown_time_;
	bool cooldown_;

};


#endif