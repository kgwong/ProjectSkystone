#ifndef FLYING_STATE_H
#define FLYING_STATE_H

#include "PlayerState.h"

class FlyingState : public PlayerState
{
public:
	static const float FLIGHT_VELOCITY;

public:
	FlyingState(GameObject& owner);
	virtual ~FlyingState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);


	virtual std::string name() { return "FlyingState"; }
};

#endif //FLYING_STATE_H