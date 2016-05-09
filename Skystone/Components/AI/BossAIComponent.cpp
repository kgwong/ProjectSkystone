#include "BossAIComponent.h"
#include "Game/GameTime.h"
#include "Application/Log.h"
#include <stdlib.h>
#include <math.h> 
#include "Components/Physics/PhysicsComponent.h"
#include "GameMath/RNG.h"
#include <string>
using namespace std;
#define SPEED 60.0f



BossAIComponent::BossAIComponent(GameObject & owner):
	AIComponent(owner),
	cooldown_time_(DEFAULT_COOLDOWN_SECONDS),
	timer_(0),
	initiate_attack_(false),
	close_range_(DEFAULT_CLOSE_RANGE),
	medium_range_(DEFAULT_MEDIUM_RANGE),
	facing_(-1),
	claw_(owner, "Boss"),
	attack_("Idle"),
	pounce_(owner, "Boss"),
	triple_shot_(owner, "Boss"),
	lazer_(owner, "Boss")
{
}


BossAIComponent::~BossAIComponent()
{
}

void BossAIComponent::start(Scene & scene)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
	claw_.start(scene);
	pounce_.start(scene);
	triple_shot_.start(scene);
	lazer_.start(scene);
}

void BossAIComponent::update(Scene & scene)
{
	timer_ += Time::getElapsedUpdateTimeSeconds();
	if (initiate_attack_)
	{
		float xDistanceFromPlayer = owner_.getPosX() - scene.gameObjects.getPlayer().getPosX();
		//temporary
		if (xDistanceFromPlayer < 0)
		{
			facing_ = 1;
		}
		else
		{
			facing_ = -1;
		}
		if ((facing_ < 0 && xDistanceFromPlayer < 0) || (facing_ > 0 && xDistanceFromPlayer > 0))
		{
			//backward tail swing, then jump back and turn around
			LOG("AARON") << "Tail swing?";
			attack_ = "tail swing";
			initiate_attack_ = false;
			physics_->setVelX(0);
		}
		//CHANGE THE Y POS CHECKER AFTER ACTUAL SIZE IS IMPLEMENTED
		else if (abs(xDistanceFromPlayer) < close_range_ && scene.gameObjects.getPlayer().getPosY() >= owner_.getPosY())
		{
			//close range attack
			LOG("AARON") << "INITIATING CLOSE RANGE ATTACK";
			attack_ = "claw attack";
			initiate_attack_ = false;
			physics_->setVelX(0);
		}
		else if (abs(xDistanceFromPlayer) < medium_range_)
		{
			physics_->setVelX(0);
			//pick between 3 attacks
			int pickAttack = RNG::getInt(0, 3);//rand() % 3;
			switch (pickAttack)
			{
			case 0:
				//jumps into air, damages area nearby when it hits the ground (stays airborn for a moment)
				LOG("AARON") << "INITIATING JUMP ATTACK";
				attack_ = "jump attack";
				break;
			case 1:
				//low damage, should be hard to dodge
				LOG("AARON") << "INITIATING TRIPLE SHOT";
				attack_ = "triple shot";
				break;
			case 2:
				//visibly charges a shot, then shoots a line, which moves for a second then stops firing
				LOG("AARON") << "INITIATING LAZER";
				attack_ = "lazer";
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
				physics_->setVelX(0);
				LOG("AARON") << "JUST IDLING";
				initiate_attack_ = false;
				break;
			case 1:
				LOG("AARON") << "WALKING AROUND";
				physics_->setVelX(xDistanceFromPlayer / abs(xDistanceFromPlayer) * -DEFAULT_MOVE_SPEED * SPEED);
				initiate_attack_ = false;
				break;
			}
		}
	}
	//if on cooldown, don't attack, possibly move around
	if (timer_ > cooldown_time_ && attack_ == "Idle")
	{
		initiate_attack_ = true;
		timer_ = 0;
	}
	else 
	{
		if (attack_ == "claw attack")
		{
			claw_.update(scene);
		}

		else if (attack_ == "jump attack")
		{
			pounce_.update(scene);
		}

		else if (attack_ == "triple shot")
		{
			triple_shot_.update(scene);
		}

		else if (attack_ == "lazer")
		{
			lazer_.update(scene);
		}
	}
}

float BossAIComponent::getFacing()
{
	return facing_;
}

void BossAIComponent::setAttack(string attack)
{
	attack_ = attack;
}

PhysicsComponent* BossAIComponent::getPhysics()
{
	return physics_;
}

float BossAIComponent::getCooldown()
{
	return cooldown_time_;
}