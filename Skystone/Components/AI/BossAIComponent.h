#ifndef BOSS_AI_COMPONENT_H
#define BOSS_AI_COMPONENT_H

#include "AIComponent.h"

class HealthComponent;
class PhysicsComponent;

class BossAIComponent :
	public AIComponent
{
public:



public:
	BossAIComponent(GameObject& owner);
	virtual ~BossAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);
};

#endif