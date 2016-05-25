#ifndef HOOK_LAUNCH_STATE_H
#define HOOK_LAUNCH_STATE_H
#include "Components\Player\Attack\Aim\PlayerAimState.h"

#include "HookStateManager.h"
class HookLaunchState : public HookStateManager
{
public:
	HookLaunchState(GameObject& owner);
	virtual ~HookLaunchState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void handleEvent(const CollisionEvent& e);
	virtual void update(Scene& scene);
	virtual std::string name();

	void instantiateHook(Scene& scene);

private:
	float degrees_;
	float hookWidth_;
	float hookHeight_;
	float hookVelocity_;
	Point hookPosition_;
	PhysicsComponent* physics_;



};

#endif

