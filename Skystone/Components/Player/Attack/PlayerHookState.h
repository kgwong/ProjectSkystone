#ifndef PLAYER_HOOK_STATE
#define PLAYER_HOOK_STATE

#include "Components/InputComponent.h"
#include "HookStateManager.h"

#include "HookLaunchState.h"
#include "HookConnectState.h"
#include "HookDisconnectState.h"

#include "Aim/AimState.h"

class PlayerHookState :
	public InputComponent
{
public:
	static const AimState DEFAULT_AIM_STATE = AimState::RIGHT;

	HookLaunchState launchState;
	HookConnectState connectState;
	HookDisconnectState disconnectState;
public:
	PlayerHookState(GameObject& owner);
	virtual ~PlayerHookState();

	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void start(Scene& scene);
	virtual void handleEvent(const CollisionEvent& e);
	void update(Scene& scene);
	
	double getDegrees();
	
	AimState& getAimState();
	void setAimState(AimState state);
	std::string AimStateName();

	void changeState(Scene& scene, const std::string& stateName);
	void resetState();

	HookStateManager* getState();
	bool enterOtherLevel;

private:
	HookStateManager* hookStateManager_;
	double _degrees;
	AimState _currentAimState;

private:
	HookStateManager* getStateFromName(const std::string& name);

};

#endif

