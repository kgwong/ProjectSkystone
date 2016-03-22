#ifndef ALLIGATOR_AI_COMPONENT_H
#define ALLIGATOR_AI_COMPONENT_H
#include "AIComponent.h"


class AlligatorAIComponent :
	public AIComponent
{

public:
	const float DEFAULT_SHORT_WALK = 30;
	const float DEFAULT_LONG_WALK = 60;
	const float DEFAULT_IDLE_TIME = 50;
	const float DEFAULT_MOVE_SPEED = 2;


public:
	AlligatorAIComponent(GameObject& owner);
	virtual ~AlligatorAIComponent();

	//virtual void start(Level& level);
	//virtual void update(Level& level);

private:
	float short_walk_, long_walk_, idle_time_, move_speed_;





};

#endif