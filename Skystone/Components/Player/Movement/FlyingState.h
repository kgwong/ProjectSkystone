#ifndef FLYING_STATE_H
#define FLYING_STATE_H

#include "PlayerState.h"

class FlyingState : public PlayerState
{
public:
	static const int FLIGHT_VELOCITY = 5;

public:
	FlyingState();
	virtual ~FlyingState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player);
	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player);


	virtual std::string name() { return "Flying"; }
};

#endif //FLYING_STATE_H