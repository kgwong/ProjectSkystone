#ifndef HOOK_DISCONNECT_STATE_H
#define HOOK_DISCONNECT_STATE_H

#include "Components\Player\Attack\PlayerAimState.h"
#include "HookStateManager.h"
class HookDisconnectState : public HookStateManager
{
public:
	HookDisconnectState(GameObject& owner);
	virtual ~HookDisconnectState();
	virtual void onEnter(Scene& scene) ;
	virtual void onExit(Scene& scene) ;
	virtual void handleInput(Scene& scene, SDL_Event& e) ;
	virtual void update(Scene& scene) ;

	virtual double getAngle();
	virtual std::string name() { return "HookDisconnectState"; }
};

#endif

