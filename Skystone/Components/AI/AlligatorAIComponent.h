#ifndef ALLIGATOR_AI_COMPONENT_H
#define ALLIGATOR_AI_COMPONENT_H
#include "AIComponent.h"


class PhysicsComponent;

class AlligatorAIComponent :
	public AIComponent
{

public:
	const double DEFAULT_SHORT_WALK = 0.3;
	const double DEFAULT_LONG_WALK = 0.6;
	const float DEFAULT_ACTION_TIME = 1.7;
	const double DEFAULT_MOVE_SPEED = 3;
	const float DEFAULT_PROJECTILE_VELOCITY = 7;


public:
	AlligatorAIComponent(GameObject& owner);
	virtual ~AlligatorAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	double short_walk_, long_walk_, move_speed_;
	double select_action_[2];
	PhysicsComponent* physics_;
	double timer_;
	float action_time_;
	bool moving_;
	double move_time_;
	double move_timer_;
	bool shot_ready_;
	double shot_timer_;




};

#endif