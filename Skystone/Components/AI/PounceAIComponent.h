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
	const float DEFAULT_JUMP_HEIGHT = -10;
	const float DEFAULT_JUMP_DISTANCE = 8;
	const float DEFAULT_RADIUS = 175.0f;
	const float PounceAIComponent::DEFAULT_COOLDOWN_TIME = 1.5;


public:
	PounceAIComponent(GameObject& owner);
	PounceAIComponent(GameObject& owner, std::string enemyType);
	virtual ~PounceAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	PhysicsComponent* physics_;
	float radius_;
	float timer_;
	float cooldown_time_;
	bool cooldown_;
	std::string enemy_type_;
	float jump_height_;
	float jump_distance_;
	BossAIComponent* boss_;


};


#endif