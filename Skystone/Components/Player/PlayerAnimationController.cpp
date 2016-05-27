#include "PlayerAnimationController.h"

#include "Movement/PlayerMovementState.h"
#include "Attack/PlayerAttackState.h"

#include "Components/Render/SpriteAnimator.h"


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
			
		}
	}
	else if (movementStateName == "WalkingState")
	{
		if (attackStateName == "AimUpState")
		{

		}
		else if (attackStateName == "AimDiagonalState")
		{
			animator_->setSpriteSheet("Images/seig heil run shoot.png");
			animator_->setTimesToPlay(-1);
		}
		else if (attackStateName == "DefaultAimState")
		{

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
}