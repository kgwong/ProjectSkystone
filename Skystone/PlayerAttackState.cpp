#include "PlayerAttackState.h"

#include "PhysicsComponent.h"

#include "Controls.h"

PlayerAttackState::PlayerAttackState(GameObject& owner)
	:InputComponent(owner),
	aimState_(AimState::RIGHT),
	degrees_(0),
	shoot_(false)
{
}


PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::handleInput(SDL_Event & e)
{
	if (e.key.keysym.sym == controlMap[ATTACK])
		shoot_ = true;

	if (aimState_ == AimState::UP)
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
	}
}

void PlayerAttackState::update(Level& level)
{
	switch (aimState_)
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
	}

	if (shoot_)
	{
		level.addPlayerProjectileAtLocation(owner_.getPos(), PROJECTILE_VELOCITY, degrees_);
		shoot_ = false;
	}
}