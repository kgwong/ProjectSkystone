#ifndef FLYING_STATE_H
#define FLYING_STATE_H

#include "PlayerState.h"

class FlyingState : public PlayerState
{
public:
	static const float FLIGHT_VELOCITY;

public:
	FlyingState();
	virtual ~FlyingState();

	virtual void onEnter(Scene& scene, GameObject& player);
	virtual void onExit(Scene& scene, GameObject& player);
	virtual void handleInput(Scene& scene, GameObject& player, SDL_Event& e);
	virtual void update(Scene& scene, GameObject& player);


	virtual std::string name() { return "Flying"; }
};

#endif //FLYING_STATE_H