#ifndef LAZER_AI_COMPONENT_H
#define LAZER_AI_COMPONENT_H
#include "AIComponent.h"
#include <string>

class BossAIComponent;

class LazerAIComponent :
	public AIComponent
{
public:
	const float DEFAULT_CHARGE_TIME = 0.7;
	const float DEFAULT_STILL_TIME = 1;
	const float DEFAULT_MOVE_TIME = 1;
	const float DEFAULT_PROJECTILE_SPEED = 15;
	const float DEFAULT_LAZER_SPEED = .3;
	const float DEFAULT_PROJECTILE_DELAY = 40;

public:
	LazerAIComponent(GameObject & owner, std::string enemyType);
	LazerAIComponent(GameObject & owner);
	virtual ~LazerAIComponent();

	void start(Scene & scene);
	void update(Scene & scene);


private:
	float charge_time_;
	float still_time_;
	float move_time_;
	float timer_;
	BossAIComponent* boss_;
	bool start_;
	std::shared_ptr<GameObject> charge_;
	bool firing_;
	float projectile_speed_;
	float offset_;
	float xDist;
	float yDist;
	float playerSide;
	float lazer_speed_;
	std::string enemy_type_;
	float Dist;
	float projectile_delay_;
	float delay_timer_;
};

#endif //LAZER_AI_COMPONENT_H

