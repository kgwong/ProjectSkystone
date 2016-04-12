#ifndef HOOK_CONNECT_STATE_H
#define HOOK_CONNECT_STATE_H

#include "Components/Player/Attack/PlayerAimState.h"
#include "HookStateManager.h"

class HookConnectState : public HookStateManager
{
public:
	HookConnectState(GameObject& owner);
	virtual ~HookConnectState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene) ;

	virtual double getAngle();
	virtual std::string name() { return "HookConnectState"; }

private:
	SDL_Keycode _keyInput;
};

#endif

