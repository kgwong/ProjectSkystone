#ifndef SHOCKWAVE_AI_COMPONENT_H
#define SHOCKWAVE_AI_COMPONENT_H
#include "AIComponent.h"

class BossAIComponent;
class ColliderComponent;

class ShockwaveAIComponent :
	public AIComponent
{
public:
	const float DEFAULT_SHOCKWAVE_TIME = 2;
	const float DEFAULT_NUM_WAVES = 10;
	const float DEFAULT_DELAY = 0.1;
	const float DEFAULT_STARTING_DISTANCE_X = 75;
	const float DEFAULT_DISTANCE_INTERVAL = 30;
	const float DEFAULT_PROJECTILE_SPEED = 1;
	
public:
	ShockwaveAIComponent(GameObject & owner, std::string enemyType);
	virtual ~ShockwaveAIComponent();

	void start(Scene & scene);
	void update(Scene & scene);

private:
	float shockwave_time_;
	float num_waves_;
	float delay_;
	float start_distance_;
	float timer_;
	std::string enemy_type_;
	BossAIComponent* boss_;
	float current_count_;
	std::vector<std::shared_ptr<GameObject>> waves_;
	ColliderComponent* collider_;
	float distance_interval_;
	float projectile_speed_;
	int facing_;


};

#endif //SHOCKWAVE_AI_COMPONENT_H