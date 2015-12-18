#ifndef PLAYER_MOVEMENT_STATE_H
#define PLAYER_MOVEMENT_STATE_H

#include "InputComponent.h"

#include "AirborneState.h"
#include "WalkingState.h"
#include "FlyingState.h"
#include "StunState.h"


class PlayerMovementState : public InputComponent
{
public:
	static WalkingState walkingState;
	static FlyingState flyingState;
	static AirborneState airborneState;
	static StunState stunState;
public:
	PlayerMovementState(GameObject& owner);
	virtual ~PlayerMovementState();

	virtual void handleInput(SDL_Event& e);

	virtual void update(Level& level);

	void changeState(PlayerState* state);

private:
	PlayerState* currentState_;
};

#endif //PLAYER_MOVEMENT_STATE_H