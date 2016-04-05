#ifndef LAUNCH_STATE_H
#define LAUNCH_STATE_H
#include "Components\Player\Movement\PlayerState.h"
class LaunchState :
	public PlayerState
{
public:
	LaunchState();
	virtual ~LaunchState();

	virtual void onEnter(Scene& scene, GameObject& player);
	virtual void onExit(Scene& scene, GameObject& player);
	virtual void handleInput(Scene& scene, GameObject& player, SDL_Event& e);
	virtual void update(Scene& scene, GameObject& player);

	virtual std::string name() { return "Launch"; }

private:
	bool someSwitch_;//extended version of kevin's hack.
	int direction_;

};

#endif;

