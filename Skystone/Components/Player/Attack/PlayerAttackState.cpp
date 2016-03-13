#include "PlayerAttackState.h"

#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/Movement/PlayerState.h"

#include "Game/GameInputs.h"

#include "Application/Log.h"

#include "Resources/Resources.h"

#include "GameMath/CircleMath.h"

DefaultAimState PlayerAttackState::defaultAimState;
AimUpState PlayerAttackState::aimUpState;

PlayerAttackState::PlayerAttackState(GameObject& owner)
	:InputComponent(owner),
	currentState_(&defaultAimState),
	aimState_(AimState::RIGHT),
	degrees_(0),
	shoot_(false)
	//launch_(false)
{
}


PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::handleInput(SDL_Event& e)
{
	currentState_->handleInput(owner_, e);
	if (GameInputs::keyDown(e, ATTACK))
	{
		shoot_ = true;
	}
	//if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[ATTACK])
	//	shoot_ = false;

	//NON SPAMMABLE SHOTS.
	/*if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[ATTACK])
		shoot_ = false;*/

	//------hook launching----//
	/*if (e.key.keysym.sym == controlMap[LAUNCH_HOOK])
	{
		launch_ = true;
	}*/



	/*if (aimState_ == AimState::UP)
	{
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
		{
			aimState_ = AimState::UP_LEFT;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
		{
			aimState_ = AimState::UP_RIGHT;
		}
		if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[UP])
		{
			aimState_ = prevAimState_;
		}
	}
	else
	{
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
		{
			aimState_ = AimState::LEFT;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
		{
			aimState_ = AimState::RIGHT;
		}
		if (e.key.keysym.sym == controlMap[UP])
		{
			if (aimState_ == AimState::LEFT || aimState_ == AimState::RIGHT)
			{
				prevAimState_ = aimState_;
			}
			aimState_ = AimState::UP;
		}
	}*/
}

void PlayerAttackState::update(Scene& scene)
{
	/*switch (aimState_)
	{
	case AimState::UP:
		degrees_ = 270;
		break;
	case AimState::UP_LEFT:
		owner_.getComponent<PhysicsComponent>()->setVelX(0);
		degrees_ = 225;
		break;
	case AimState::UP_RIGHT:
		owner_.getComponent<PhysicsComponent>()->setVelX(0);
		degrees_ = 315;
		break;
	case AimState::LEFT:
		degrees_ = 180;
		break;
	case AimState::RIGHT:
		degrees_ = 0;
		break;
	}*/
	
	currentState_->update(owner_);
	degrees_ = currentState_->getAngle();
	//LOG << "degrees: " << degrees_;
	//LOG << "owner pos: " << owner_.getPos().x << ", " << owner_.getPos().y;
	if (shoot_)
	{
		//level.addPlayerProjectileAtLocation(owner_.getPos(), PROJECTILE_VELOCITY, degrees_);
		auto bullet = scene.gameObjects.add("PlayerProjectile", "", owner_.getPos());
		auto physics = bullet->getComponent<PhysicsComponent>();
		float newVelX = (float)PROJECTILE_VELOCITY * cos(toRadians(degrees_));
		float newVelY = (float)PROJECTILE_VELOCITY * sin(toRadians(degrees_));
		physics->setVelX(newVelX * 60.0f);
		physics->setVelY(newVelY * 60.0f);
		shoot_ = false;

		Resources::audioPlayer.PlayClip("laser1");
	}


	/*if (launch_)
	{
		int testVelocity = 5;
		level.addPlayerHookAtLocation(owner_.getPos(), testVelocity, degrees_);
		launch_ = false;
	}*/
}

void PlayerAttackState::changeState(PlayerAimState* state)
{
	currentState_->onExit(owner_);
	currentState_ = state;
	currentState_->onEnter(owner_);
}
