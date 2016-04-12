#include "BossAIComponent.h"
#include "Game/GameTime.h"
#include "Application/Log.h"
#include <stdlib.h>
#include <math.h> 
#include "Components/Physics/PhysicsComponent.h"
#include "GameMath/RNG.h"
#include <string>
using namespace std;



BossAIComponent::BossAIComponent(GameObject & owner):
	AIComponent(owner),
	cooldown_time_(DEFAULT_COOLDOWN_SECONDS),
	timer_(0),
	initiate_attack_(false),
	close_range_(DEFAULT_CLOSE_RANGE),
	medium_range_(DEFAULT_MEDIUM_RANGE),
	facing_(-1),
	claw_(owner),
	attack_("Idle")
{
}


BossAIComponent::~BossAIComponent()
{
}

void BossAIComponent::start(Scene & scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	claw_.start(scene);
}

void BossAIComponent::update(Scene & scene)
{
	timer_ += Time::getElapsedUpdateTimeSeconds();
	if (initiate_attack_)
	{
		float xDistanceFromPlayer = owner_.getPosX() - scene.gameObjects.getPlayer().getPosX();
		if ((facing_ < 0 && xDistanceFromPlayer < 0) || (facing_ > 0 && xDistanceFromPlayer > 0))
		{
			//backward tail swing, then jump back and turn around
			initiate_attack_ = false;
		}
		//CHANGE THE Y POS CHECKER AFTER ACTUAL SIZE IS IMPLEMENTED
		else if (abs(xDistanceFromPlayer) < close_range_ && scene.gameObjects.getPlayer().getPosY() < owner_.getPosY())
		{
			//close range attack
			attack_ = "Tail swing";
			initiate_attack_ = false;
		}
		else if (scene.gameObjects.getPlayer().getPosX() < medium_range_)
		{
			//pick between 3 attacks
			int pickAttack = RNG::getInt(0, 3);//rand() % 3;
			switch (pickAttack)
			{
			case 0:
				//jumps into air, damages area nearby when it hits the ground (stays airborn for a moment)
				LOG("AARON") << "INITIATING JUMP ATTACK";
				break;
			case 1:
				//low damage, should be hard to dodge
				LOG("AARON") << "INITIATING TRIPLE SHOT";
				break;
			case 2:
				//visibly charges a shot, then shoots a line, which moves for a second then stops firing
				LOG("AARON") << "INITIATING LAZER";
				break;
			}
			initiate_attack_ = false;
		}
		else
		{
			int pickMove = RNG::getInt(0, 2);//rand() % 2;

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
		initiate_attack_ = true;
		timer_ = 0;

	}
	else 
	{
		if (attack_ == "Tail swing")
		{
			claw_.update(scene);
		}
	}
}

float BossAIComponent::getFacing()
{
	return facing_;
}