#ifndef PLAYER_ATTACK_STATE_H
#define PLAYER_ATTACK_STATE_H

#include "Components/InputComponent.h"

#include "Aim/PlayerAimState.h"
#include "Aim/DefaultAimState.h"

#include "PlayerHookState.h"
class PlayerAttackState : public InputComponent
{
public:
	static const int PROJECTILE_VELOCITY = 20;

	DefaultAimState defaultAimState;

	//the hook states
	//static LaunchHookState launchstate;
	//static ConnectHookState connectState;
	//static DisconnectHookState disconnectState;

public:
	PlayerAttackState(GameObject& owner);
	virtual ~PlayerAttackState();

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	void changeState(Scene& scene, const std::string& stateName);

private:
	PlayerAimState* currentState_;
	AimState prevAimState_;
	double degrees_;
	bool shoot_;

private:
	PlayerAimState* getStateFromName(const std::string& name);

};

#endif //PLAYER_ATTACK_STATE_H