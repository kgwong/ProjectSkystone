#ifndef HOOK_LAUNCH_STATE_H
#define HOOK_LAUNCH_STATE_H
#include "Components\Player\Attack\PlayerAimState.h"

#include "HookStateManager.h"
class HookLaunchState : public HookStateManager
{
public:
	HookLaunchState(GameObject& owner);
	virtual ~HookLaunchState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	virtual double getAngle();
	virtual std::string name() { return "HookLaunchState"; }

};

#endif

