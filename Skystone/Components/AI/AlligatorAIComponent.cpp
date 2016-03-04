#include "AlligatorAIComponent.h"



AlligatorAIComponent::AlligatorAIComponent(GameObject & owner)
	:AIComponent(owner),
	short_walk_(DEFAULT_SHORT_WALK),
	long_walk_(DEFAULT_LONG_WALK),
	idle_time_(DEFAULT_IDLE_TIME),
	move_speed_(DEFAULT_MOVE_SPEED)
	
{
}


AlligatorAIComponent::~AlligatorAIComponent()
{
}

