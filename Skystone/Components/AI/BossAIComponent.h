#ifndef BOSS_AI_COMPONENT_H
#define BOSS_AI_COMPONENT_H

#include "AIComponent.h"

class HealthComponent;
class PhysicsComponent;

class BossAIComponent :
	public AIComponent
{
public:
	const float DEFAULT_COOLDOWN_SECONDS = 5;
	const float DEFAULT_CLOSE_RANGE = 500;
	const float DEFAULT_MEDIUM_RANGE = 750;


public:
	BossAIComponent(GameObject& owner);
	virtual ~BossAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	float cooldown_time_;
	double timer_;
	bool cooldown_;
	float close_range_;
	float medium_range_;
};

#endif