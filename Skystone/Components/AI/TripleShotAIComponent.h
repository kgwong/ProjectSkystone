#ifndef TRIPLE_SHOT_AI_COMPONENT_H
#define TRIPLE_SHOT_AI_COMPONENT_H

#include "AIComponent.h"
#include "GameTypes/Point.h"
#include <string>;

class BossAIComponent;

class TripleShotAIComponent :
	public AIComponent
{
public:
	const float DEFAULT_PROJECTILE_DELAY = 0.1;
	const float DEFAULT_PROJECTILE_SPEED = 8;
	const float DEFAULT_PROJECTILE_COUNT = 4;
	const float DEFAULT_COOLDOWN_TIME = 4.5;
	


public:
	TripleShotAIComponent(GameObject & owner, std::string enemy_type);
	virtual ~TripleShotAIComponent();

	virtual void start(Scene & scene);
	virtual void update(Scene & scene);


private:
	float delay_;
	float timer_;
	float projectile_speed_;
	std::string enemy_type_;
	bool cooldown_;
	bool firing_;
	int projectile_count_;
	int current_count_;
	float cooldown_time_;
	float xDist;
	float yDist;
	float playerSide;
	BossAIComponent* boss_;
};

#endif //TRIPLE_SHOT_AI_COMPONENT_H