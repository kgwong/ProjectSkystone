#ifndef SHOCKWAVE_AI_COMPONENT_H
#define SHOCKWAVE_AI_COMPONENT_H
#include "AIComponent.h"

class ShockwaveAIComponent :
	public AIComponent
{
public:
	const float DEFAULT_SHOCKWAVE_TIME = 1;
	const float DEFAULT_NUM_WAVES = 6;
	const float DEFAULT_DELAY = 1;
	const float DEFAULT_STARTING_DISTANCE = 50;
	
public:
	ShockwaveAIComponent(GameObject & owner, std::string enemyType);
	virtual ~ShockwaveAIComponent();

	void start(Scene & scene);
	void update(Scene & scene);

private:
	float shockwave_time_;
	float num_waves_;
	float delay_;
	float starting_distance_;
	float timer_;
	std::string enemy_type_;

};

#endif //SHOCKWAVE_AI_COMPONENT_H