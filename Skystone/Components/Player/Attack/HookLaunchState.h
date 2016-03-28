#ifndef HOOK_LAUNCH_STATE_H
#define HOOK_LAUNCH_STATE_H
#include "Components\Player\Attack\PlayerAimState.h"

#include "HookStateManager.h"
class HookLaunchState : public HookStateManager
{
public:
	HookLaunchState();
	virtual ~HookLaunchState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player);
	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player);

	virtual double getAngle();
	virtual std::string name() { return "HookLaunchState"; }

};

#endif

