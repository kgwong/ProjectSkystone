#ifndef HOOK_DISCONNECT_STATE_H
#define HOOK_DISCONNECT_STATE_H

#include "Components\Player\Attack\Aim\PlayerAimState.h"
#include "Components/Player/Attack/Aim/AimState.h"
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
	virtual std::string name();

	float getDegrees();
	AimState& getAimState();
	void setAimState(AimState aim);

	void disconnectHook(Scene& scene);

private:
	AimState playerAim_;
	float degrees_;

};

#endif

