#ifndef PLAYER_ATTACK_STATE_H
#define PLAYER_ATTACK_STATE_H

#include "Components/InputComponent.h"

#include "PlayerAimState.h"
#include "DefaultAimState.h"
#include "AimUpState.h"
#include "AudioPlayer.h"

class PlayerAttackState : public InputComponent
{
public:
	enum class AimState
	{
		UP, LEFT, RIGHT, UP_LEFT, UP_RIGHT
	};

	static const int PROJECTILE_VELOCITY = 20;

	static DefaultAimState defaultAimState;
	static AimUpState aimUpState;

public:
	PlayerAttackState(GameObject& owner);
	virtual ~PlayerAttackState();

	virtual void handleInput(SDL_Event& e);
	virtual void update(Level& level);

	void changeState(PlayerAimState* state);

private:
	PlayerAimState* currentState_;
	AimState aimState_;
	AimState prevAimState_;
	double degrees_;
	bool shoot_;

	//for hook ~ move to a different state
	//bool launch_;

	AudioPlayer audio_;

};

#endif //PLAYER_ATTACK_STATE_H