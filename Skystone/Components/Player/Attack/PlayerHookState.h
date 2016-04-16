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

	HookLaunchState launchState;
	HookConnectState connectState;
	HookDisconnectState disconnectState;
public:
	PlayerHookState(GameObject& owner);
	~PlayerHookState();

	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	void update(Scene& scene);
	double getDegrees();
	void changeState(Scene& scene, const std::string& stateName);

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

private:
	HookStateManager* getStateFromName(const std::string& name);

};

#endif

