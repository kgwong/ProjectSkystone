#ifndef PLAYER_ATTACK_STATE_H
#define PLAYER_ATTACK_STATE_H

#include "InputComponent.h"

class PlayerAttackState : public InputComponent
{
public:
	enum class AimState
	{
		UP, LEFT, RIGHT, UP_LEFT, UP_RIGHT
	};

	static const int PROJECTILE_VELOCITY = 20;

public:
	PlayerAttackState(GameObject& owner);
	virtual ~PlayerAttackState();

	virtual void handleInput(SDL_Event& e);

	virtual void update(Level& level);

private:
	AimState aimState_;
	AimState prevAimState_;
	double degrees_;
	bool shoot_;

};

#endif //PLAYER_ATTACK_STATE_H