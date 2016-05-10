#include "ShockwaveAIComponent.h"



ShockwaveAIComponent::ShockwaveAIComponent(GameObject& owner, std::string enemyType) :
	AIComponent(owner),
	shockwave_time_(DEFAULT_SHOCKWAVE_TIME),
	num_waves_(DEFAULT_NUM_WAVES),
	delay_(DEFAULT_DELAY),
	starting_distance_(DEFAULT_STARTING_DISTANCE),
	timer_(0),
	enemy_type_(enemyType)
{
}


ShockwaveAIComponent::~ShockwaveAIComponent()
{
}

void ShockwaveAIComponent::start(Scene& scene)
{

}

void ShockwaveAIComponent::update(Scene& scene)
{

}