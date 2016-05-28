#ifndef PLAYER_ANIMATION_CONTROLLER_H
#define PLAYER_ANIMATION_CONTROLLER_H

#include "GameTypes/FacingDirection.h"

class PlayerMovementState;
class PlayerAttackState;
class SpriteAnimator;
class PlayerControlComponent;

//this class really shouldn't handle shooting offsets, but it does for now

class PlayerAnimationController
{
public:
	PlayerAnimationController();
	~PlayerAnimationController();

	void setAnimator(SpriteAnimator* animator);

	void updatePlayerSpriteFlip(FacingDirection facingDirection);
	void changeAnimation(PlayerMovementState& movementState, PlayerAttackState& attackState);

	void calculateShootOffset(PlayerMovementState& movementState, PlayerAttackState& attackState);

private:
	SpriteAnimator* animator_;
	FacingDirection facingDirection_;
};

#endif //PLAYER_ANIMATION_CONTROLLER_H
