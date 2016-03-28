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

	virtual void handleInput(SDL_Event& e);
	void update(Scene& scene);
	double getDegrees();
	void changeState(HookStateManager* state);

	std::shared_ptr<GameObject> hookRef;
	void instantiateHook(Scene& scene);
	void connectHook(Scene& scene);
	void disconnectHook(Scene& scene);
	void resetState();
	HookStateManager* getState();
	Point getPosition();
	bool hanging;

	//delete these.. later.
	void setLaunched(bool b);
	bool hasLaunched();
	bool isActiveHook();
	SDL_Keycode getKeyInput();
private:
	HookStateManager* hookStateManager_;
	double _degrees;

	//delete these useless variables later.
	bool _launched;
	bool _hookActive;
	AimState _currentAimState;
	SDL_Keycode _keyInput;
};

#endif

