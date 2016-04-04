#ifndef PLAYER_HOOK_STATE
#define PLAYER_HOOK_STATE

#include "Components/InputComponent.h"
#include "AimState.h"
#include "HookStateManager.h"

#include "HookLaunchState.h"
#include "HookConnectState.h"
#include "HookDisconnectState.h"

class PlayerHookState :
	public InputComponent
{
public:
	static const AimState DEFAULT_AIM_STATE = AimState::RIGHT;

	//static states.
	static HookLaunchState launchState;
	static HookConnectState connectState;
	static HookDisconnectState disconnectState;
public:
	PlayerHookState(GameObject& owner);
	~PlayerHookState();

	virtual void handleInput(Scene& scene, SDL_Event& e);
	void update(Scene& scene);
	double getDegrees();
	void changeState(Scene& scene, HookStateManager* state);

	std::shared_ptr<GameObject> hookRef;
	void instantiateHook(Scene& scene);
	void connectHook(Scene& scene);
	void disconnectHook(Scene& scene);
	void resetState();

	HookStateManager* getState();
	Point getPosition();
	void setHanging(bool h);
	bool hanging;
	bool enterOtherLevel;

	virtual void handleEvent(const CollisionEvent& e);

private:
	HookStateManager* hookStateManager_;
	double _degrees;
	AimState _currentAimState;

};

#endif

