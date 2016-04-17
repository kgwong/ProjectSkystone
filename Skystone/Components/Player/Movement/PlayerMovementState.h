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
	WalkingState walkingState;
	FlyingState flyingState;
	AirborneState airborneState;
	StunState stunState;
	HangState hangState;
	LaunchState launchState;
public:
	PlayerMovementState(GameObject& owner);
	virtual ~PlayerMovementState();

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	void changeState(Scene& scene, const std::string& stateName);
	PlayerState* getState();
	virtual void handleEvent(const CollisionEvent& e);
	void setCanSwing(bool swing);
	bool canSwing;
	void setDirection(int dir);
	int direction;

private:
	PlayerState* currentState_;

private:
	PlayerState* getStateFromName(const std::string& name);
};

#endif //PLAYER_MOVEMENT_STATE_H