#ifndef PLAYER_ANIMATION_CONTROLLER_H
#define PLAYER_ANIMATION_CONTROLLER_H

#include "GameTypes/FacingDirection.h"

class PlayerMovementState;
class PlayerAttackState;
class SpriteAnimator;

class PlayerAnimationController
{
public:
	PlayerAnimationController();
	~PlayerAnimationController();

	void setAnimator(SpriteAnimator* animator);

	void updatePlayerSpriteFlip(FacingDirection facingDirection);
	void changeAnimation(PlayerMovementState& movementState, PlayerAttackState& attackState);

private:
	SpriteAnimator* animator_;
};

#endif //PLAYER_ANIMATION_CONTROLLER_H
