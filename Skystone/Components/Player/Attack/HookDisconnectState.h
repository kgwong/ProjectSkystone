#ifndef HOOK_DISCONNECT_STATE_H
#define HOOK_DISCONNECT_STATE_H

#include "Components\Player\Attack\PlayerAimState.h"
#include "HookStateManager.h"
class HookDisconnectState : public HookStateManager
{
public:
	HookDisconnectState();
	virtual ~HookDisconnectState();
	virtual void onEnter(GameObject& player) ;
	virtual void onExit(GameObject& player) ;
	virtual void handleInput(GameObject& player, SDL_Event& e) ;
	virtual void update(GameObject& player) ;

	virtual double getAngle();
	virtual std::string name() { return "HookDisconnectState"; }
};

#endif
