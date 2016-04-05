#include "BossAIComponent.h"
#include "Game/GameTime.h"
#include "Application/Log.h"
#include <stdlib.h>
#include <math.h> 
#include "Components/Physics/PhysicsComponent.h"

using namespace std;



BossAIComponent::BossAIComponent(GameObject & owner):
	AIComponent(owner),
	cooldown_time_(DEFAULT_COOLDOWN_SECONDS),
	timer_(0),
	cooldown_(true),
	close_range_(DEFAULT_CLOSE_RANGE),
	medium_range_(DEFAULT_MEDIUM_RANGE),
	facing_(-1)
{
}


BossAIComponent::~BossAIComponent()
{
}

void BossAIComponent::start(Scene & scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void BossAIComponent::update(Scene & scene)
{
	timer_ += Time::getElapsedUpdateTimeSeconds();
	if (!cooldown_)
	{
		LOG("INFO") << "player Y: " << scene.gameObjects.getPlayer().getPosY();
		LOG("INFO") << "boss Y: " << owner_.getPosY();
		float xDistanceFromPlayer = owner_.getPosX() - scene.gameObjects.getPlayer().getPosX();
		if ((facing_ < 0 && xDistanceFromPlayer < 0) || (facing_ > 0 && xDistanceFromPlayer > 0))
		{
			//backward tail swing, then jump back and turn around
			LOG("INFO") << "INITIATING TAIL SWING";
			cooldown_ = true;
		}
		//CHANGE THE Y POS CHECKER AFTER ACTUAL SIZE IS IMPLEMENTED
		else if (abs(xDistanceFromPlayer) < close_range_ && scene.gameObjects.getPlayer().getPosY() < owner_.getPosY())
		{
			//close range attack
			LOG("INFO") << "INITIATING SHORT RANGE ATTACK";
			cooldown_ = true;
		}
		else if (scene.gameObjects.getPlayer().getPosX() < medium_range_)
		{
			//pick between 3 attacks
			int pickAttack = rand() % 3;
			switch (pickAttack)
			{
			case 0:
				//jumps into air, damages area nearby when it hits the ground (stays airborn for a moment)
				LOG("INFO") << "INITIATING JUMP ATTACK";
				break;
			case 1:
				//low damage, should be hard to dodge
				LOG("INFO") << "INITIATING TRIPLE SHOT";
				break;
			case 2:
				//visibly charges a shot, then shoots a line, which moves for a second then stops firing
				LOG("INFO") << "INITIATING LAZER";
				break;
			}
			cooldown_ = true;
		}
		else
		{
			int pickMove = rand() % 2;

			switch (pickMove)
			{
			case 0:
				break;
			case 1:
				physics_->setVelX(xDistanceFromPlayer / abs(xDistanceFromPlayer) * DEFAULT_MOVE_SPEED);
				break;
			}
		}
	}
	//if on cooldown, don't attack, possibly move around
	if (timer_ > cooldown_time_)
	{
		cooldown_ = false;
		timer_ = 0;
	}
}