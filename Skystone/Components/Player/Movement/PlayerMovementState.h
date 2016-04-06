#ifndef PLAYER_MOVEMENT_STATE_H
#define PLAYER_MOVEMENT_STATE_H

#include "Components/InputComponent.h"

#include "AirborneState.h"
#include "WalkingState.h"
#include "FlyingState.h"
#include "StunState.h"

#include "HangState.h"
#include "LaunchState.h"

class PlayerMovementState : public InputComponent
{
public:
	static WalkingState walkingState;
	static FlyingState flyingState;
	static AirborneState airborneState;
	static StunState stunState;
	static HangState hangState;
	static LaunchState launchState;
public:
	PlayerMovementState(GameObject& owner);
	virtual ~PlayerMovementState();

	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	void changeState(Scene& scene, PlayerState* state);
	PlayerState* getState();
	virtual void handleEvent(const CollisionEvent& e);
	void setCanSwing(bool swing);
	bool canSwing;
	void setDirection(int dir);
	int direction;

private:
	PlayerState* currentState_;
};

#endif //PLAYER_MOVEMENT_STATE_H