#include "BossAIComponent.h"
#include "Game/GameTime.h"
#include "Application/Log.h"



BossAIComponent::BossAIComponent(GameObject & owner):
	AIComponent(owner),
	cooldown_time_(DEFAULT_COOLDOWN_SECONDS),
	timer_(0),
	cooldown_(true),
	close_range_(DEFAULT_CLOSE_RANGE),
	medium_range_
{
}


BossAIComponent::~BossAIComponent()
{
}

void BossAIComponent::start(Scene & scene)
{

}

void BossAIComponent::update(Scene & scene)
{
	timer_ += Time::getElapsedUpdateTimeSeconds();
	if (!cooldown_)
	{
		LOG("INFO") << "player Y: " << scene.gameObjects.getPlayer().getPosY();
		LOG("INFO") << "boss Y: " << owner_.getPosY();
		if (scene.gameObjects.getPlayer().getPosX() < close_range_ && scene.gameObjects.getPlayer().getPosY() < owner_.getPosY())
		{
			LOG("INFO") << "in range for attack";
			//close range attack
		}
		else if (scene.gameObjects.getPlayer().getPosX() < medium_range_)
		{
			//pick between 3 attacks
		}
	}
	if (timer_ > cooldown_time_)
	{
		cooldown_ = false;
		timer_ = 0;
	}
}