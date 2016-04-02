#ifndef HOOK_STATE_MANAGER_H
#define HOOK_STATE_MANAGER_H
#include "Components\Player\Movement\PlayerState.h"
class HookStateManager :
	public PlayerState
{
public:
	HookStateManager();
	virtual ~HookStateManager();
	virtual std::string name() { return "Hook State Manager"; }

	//tricky hacks
	//virtual void update(GameObject& player, Scene& scene) = 0;
};
#endif

