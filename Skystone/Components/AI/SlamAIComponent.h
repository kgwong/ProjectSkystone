#ifndef SLAM_AI_COMPONENT_H
#define SLAM_AI_COMPONENT_H


#include "AIComponent.h"

class PhysicsComponent;
class HealthComponent;

class SlamAIComponent :
	public AIComponent
{

public:
	const double DEFAULT_WINDUP_TIME = 0.4;
	const double DEFAULT_WINDUP_SPEED = 1;


public:
	SlamAIComponent(GameObject& owner);
	virtual ~SlamAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	PhysicsComponent* physics_;
	HealthComponent * health_;
	bool attack_initiated_;
	double timer_;
	double windup_time_;
	double windup_speed_;
	
};

#endif //SLAM_AI_COMPONENT_H