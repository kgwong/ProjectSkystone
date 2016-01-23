#include "PlayerAttackState.h"

#include "PhysicsComponent.h"
#include "PlayerState.h"

#include "PlayerMovementState.h" //
#include "Controls.h"

#include "Log.h"

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
	if (e.key.keysym.sym == controlMap[ATTACK])
		shoot_ = true;
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

void PlayerAttackState::update(Level& level)
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
		level.addPlayerProjectileAtLocation(owner_.getPos(), PROJECTILE_VELOCITY, degrees_);
		shoot_ = false;
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
