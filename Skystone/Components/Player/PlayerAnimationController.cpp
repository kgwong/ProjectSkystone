#include "PlayerAnimationController.h"

#include "Movement/PlayerMovementState.h"
#include "Attack/PlayerAttackState.h"

#include "Components/Render/SpriteAnimator.h"

#include "Application/Log.h"

PlayerAnimationController::PlayerAnimationController()
	:animator_(nullptr)
{
}


PlayerAnimationController::~PlayerAnimationController()
{
}

void PlayerAnimationController::setAnimator(SpriteAnimator* animator)
{
	animator_ = animator;
}

void PlayerAnimationController::updatePlayerSpriteFlip(FacingDirection facingDirection)
{
	switch (facingDirection)
	{
	case FacingDirection::LEFT:
		animator_->setFlipHorz(true);
		break;
	case FacingDirection::RIGHT:
		animator_->setFlipHorz(false);
		break;
	default:
		__debugbreak();
	}

	facingDirection_ = facingDirection;
}

void PlayerAnimationController::changeAnimation(PlayerMovementState& movementState, PlayerAttackState& attackState)
{
	std::string movementStateName = movementState.getState()->name();
	std::string attackStateName = attackState.getCurrentState()->name();
	if (movementStateName == "LockMovementState")
	{
		if (attackStateName == "AimUpState")
		{
			animator_->setSpriteSheet("Images/fire cycle standing.png");
			animator_->setSpriteIndex(2);
			animator_->setTimesToPlay(0);
		}
		else if (attackStateName == "AimDiagonalState")
		{
			animator_->setSpriteSheet("Images/fire cycle standing.png");
			animator_->setSpriteIndex(1);
			animator_->setTimesToPlay(0);
		}
		else if (attackStateName == "DefaultAimState")
		{
			//shouldn't happen
		}
	}
	else if (movementStateName == "WalkingState")
	{
		if (attackStateName == "AimUpState")
		{
			//shoudln't happen
		}
		else if (attackStateName == "AimDiagonalState")
		{
			animator_->setSpriteSheet("Images/seig heil run shoot.png");
			animator_->setTimesToPlay(-1);
		}
		else if (attackStateName == "DefaultAimState")
		{
			animator_->setSpriteSheet("Images/forward shoot run cycle.png");
			animator_->setTimesToPlay(-1);
		}
	}
	else if (movementStateName == "IdleState")
	{
		if (attackStateName == "AimUpState")
		{
			animator_->setSpriteSheet("Images/fire cycle standing.png");
			animator_->setSpriteIndex(2);
			animator_->setTimesToPlay(0);
		}
		else if (attackStateName == "AimDiagonalState")
		{
			// shouldn't happen
		}
		else if (attackStateName == "DefaultAimState")
		{
			animator_->setSpriteSheet("Images/fire cycle standing.png");
			animator_->setSpriteIndex(0);
			animator_->setTimesToPlay(0);
		}
	}
	else if (movementStateName == "FlyingState")
	{
		if (attackStateName == "AimUpState")
		{
			animator_->setSpriteSheet("Images/shoot up fly cycle.png");
			animator_->setTimesToPlay(1);
		}
		else if (attackStateName == "AimDiagonalState")
		{
			animator_->setSpriteSheet("Images/seig heil fly shoot.png");
			animator_->setTimesToPlay(1);
		}
		else if (attackStateName == "DefaultAimState")
		{
			animator_->setSpriteSheet("Images/fly shoot forward.png");
			animator_->setTimesToPlay(1);
		}
	}
	else if (movementStateName == "AirborneState")
	{
		if (attackStateName == "AimUpState")
		{
			animator_->setSpriteSheet("Images/Player/Jump/shoot_up_jump_cycle_truncated.png");
			animator_->setTimesToPlay(1);
		}
		else if (attackStateName == "AimDiagonalState")
		{
			animator_->setSpriteSheet("Images/Player/Jump/seig_heil_jump_shoot_truncated.png");
			animator_->setTimesToPlay(1);
		}
		else if (attackStateName == "DefaultAimState")
		{
			animator_->setSpriteSheet("Images/Player/Jump/shoot_forward_jump_truncated.png");
			animator_->setTimesToPlay(1);
		}
	}
	else if (movementStateName == "AirborneState")
	{
		if (attackStateName == "AimUpState")
		{
			animator_->setSpriteSheet("Images/Player/Jump/shoot_up_jump_cycle_truncated.png");
			animator_->setTimesToPlay(1);
		}
		else if (attackStateName == "AimDiagonalState")
		{
			animator_->setSpriteSheet("Images/Player/Jump/seig_heil_jump_shoot_truncated.png");
			animator_->setTimesToPlay(1);
		}
		else if (attackStateName == "DefaultAimState")
		{
			animator_->setSpriteSheet("Images/Player/Jump/shoot_forward_jump_truncated.png");
			animator_->setTimesToPlay(1);
		}
	}
	else if (movementStateName == "CrouchState")
	{
		animator_->setSpriteSheet("Images/crouch_shoot.png");
		animator_->setTimesToPlay(1);
	}

	calculateShootOffset(movementState, attackState);
}

void PlayerAnimationController::calculateShootOffset(PlayerMovementState& movementState, PlayerAttackState& attackState)
{
	std::string movementStateName = movementState.getState()->name();
	std::string attackStateName = attackState.getCurrentState()->name();
	int x;
	int y;
	if (attackStateName == "AimUpState")
	{
		x = 16;
		y = 0;
	}
	else if (attackStateName == "AimDiagonalState")
	{
		x = 44;
		y = 4;
	}
	else if (attackStateName == "DefaultAimState")
	{
		x = 48;
		y = 22;
	}
	if (facingDirection_ == FacingDirection::LEFT)
		x = 48 - x;

	if (movementStateName == "CrouchState")
	{
		y = 30;
	}

	attackState.setShootOffset(Point(x, y));
}
