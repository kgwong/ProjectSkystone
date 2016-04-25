#ifndef POUNCE_AI_COMPONENT_H
#define POUNCE_AI_COMPONENT_H

#include "AIComponent.h"
#include <string>

class PhysicsComponent;
class ColliderComponent;
class BossAIComponent;

class PounceAIComponent :
	public AIComponent
{

public:
	//use Time::
	const double DEFAULT_JUMP_HEIGHT = -10;
	const double DEFAULT_JUMP_DISTANCE = 7;
	const double DEFAULT_RADIUS = 175.0f;
	const double PounceAIComponent::DEFAULT_COOLDOWN_TIME = 1.5;


public:
	PounceAIComponent(GameObject& owner, std::string enemyType);
	virtual ~PounceAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	PhysicsComponent* physics_;
	double radius_;
	double timer_;
	double cooldown_time_;
	bool cooldown_;
	std::string enemy_type_;
	double jump_height_;
	double jump_distance_;
	BossAIComponent* boss_;


};


#endif