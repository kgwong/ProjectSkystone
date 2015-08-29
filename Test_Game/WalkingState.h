#ifndef WALKING_STATE_H
#define WALKING_STATE_H

#include "PlayerState.h"
#include "Direction.h"

class Player;

class WalkingState : public PlayerState
{
public:
	WalkingState();
	virtual ~WalkingState();

	virtual void onEnter(Player& player);
	virtual void onExit(Player& player);
	virtual void handleInput(Player& player, SDL_Event& e);
	virtual void update(Player& player);

	virtual std::string name() { return "Walking"; }
};

#endif // WALKING_STATE_H