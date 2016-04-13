#ifndef HOOK_STATE_MANAGER_H
#define HOOK_STATE_MANAGER_H
#include "Components\Player\Movement\PlayerState.h"
class HookStateManager :
	public PlayerState
{
public:
	HookStateManager(GameObject& owner);
	virtual ~HookStateManager();
	virtual std::string name() { return "Hook State Manager"; }

};
#endif

