#ifndef BOSS_AI_COMPONENT_H
#define BOSS_AI_COMPONENT_H


#include "SlamAIComponent.h"
#include "PounceAIComponent.h"
#include "TripleShotAIComponent.h"
#include "LazerAIComponent.h"
#include "ShockwaveAIComponent.h"
#include <string>

class PhysicsComponent;

class BossAIComponent :
	public AIComponent
{
public:
	const float DEFAULT_COOLDOWN_SECONDS = 2;
	const float DEFAULT_CLOSE_RANGE = 200;
	const float DEFAULT_MEDIUM_RANGE = 700;
	const float DEFAULT_MOVE_SPEED = 3;


public:
	BossAIComponent(GameObject& owner);
	virtual ~BossAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	float getFacing();
	PhysicsComponent * getPhysics();
	float getCooldown();
	void setAttack(std::string attack);

private:
	float cooldown_time_;
	double timer_;
	bool initiate_attack_;
	float close_range_;
	float medium_range_;
	float facing_;
	std::string attack_;
	PhysicsComponent* physics_;
	SlamAIComponent claw_;
	PounceAIComponent pounce_;
	TripleShotAIComponent triple_shot_;
	LazerAIComponent lazer_;
	ShockwaveAIComponent shockwave_;

};

#endif