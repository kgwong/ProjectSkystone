#ifndef SLAM_AI_COMPONENT_H
#define SLAM_AI_COMPONENT_H

#include <string>
#include "AIComponent.h"

class BossAIComponent;
class PhysicsComponent;
class HealthComponent;

class SlamAIComponent :
	public AIComponent
{

public:
	const double DEFAULT_WINDUP_TIME = 0.4;
	const double DEFAULT_WINDUP_SPEED = 1;
	const double DEFAULT_SWING_SPEED = 6;
	const double DEFAULT_SWING_TIME = 0.7;
	const double DEFAULT_LAG_TIME = 0.3;


public:
	SlamAIComponent(GameObject& owner);
	SlamAIComponent(GameObject& owner, std::string enemyType);
	virtual ~SlamAIComponent();

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

private:
	PhysicsComponent* physics_;
	HealthComponent* health_;
	BossAIComponent* boss_;
	bool attack_initiated_;
	double timer_;
	double windup_time_;
	double windup_speed_;
	std::shared_ptr<GameObject> claw_;
	PhysicsComponent* claw_physics_;
	double swing_speed_;
	double swing_time_;
	double lag_time_;
	std::string enemy_type_;
	
};

#endif //SLAM_AI_COMPONENT_H