#ifndef HOOK_CONNECT_STATE_H
#define HOOK_CONNECT_STATE_H

#include "Components/Player/Attack/PlayerAimState.h"
#include "HookStateManager.h"

class HookConnectState : public HookStateManager
{
public:
	HookConnectState();
	virtual ~HookConnectState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player);
	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player) ;

	virtual double getAngle();
	virtual std::string name() { return "HookConnectState"; }

private:
	SDL_Keycode _keyInput;
};

#endif

