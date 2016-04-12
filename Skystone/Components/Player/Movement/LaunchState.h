#ifndef LAUNCH_STATE_H
#define LAUNCH_STATE_H
#include "Components\Player\Movement\PlayerState.h"
class LaunchState :
	public PlayerState
{
public:
	LaunchState(GameObject& owner);
	virtual ~LaunchState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	virtual std::string name() { return "Launch"; }

private:
	bool someSwitch_;//extended version of kevin's hack.
	int direction_;

};

#endif;

