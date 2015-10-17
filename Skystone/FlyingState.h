#ifndef FLYING_STATE_H
#define FLYING_STATE_H

#include "PlayerState.h"

class FlyingState : public PlayerState
{
public:
	FlyingState();
	virtual ~FlyingState();

	virtual void onEnter(Player& player);
	virtual void onExit(Player& player);
	virtual void handleInput(Player& player, SDL_Event& e);
	virtual void update(Player& player);


	virtual std::string name() { return "Flying"; }
};

#endif //FLYING_STATE_H