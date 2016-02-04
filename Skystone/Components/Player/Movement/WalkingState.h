#ifndef WALKING_STATE_H
#define WALKING_STATE_H

#include "PlayerState.h"
#include "Direction.h"

class WalkingState : public PlayerState
{
public:
	static const int JUMP_VELOCITY = -20;
	static const int WALK_VELOCITY = 5;

public:
	WalkingState();
	virtual ~WalkingState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player);
	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player);

	virtual std::string name() { return "Walking"; }
};

#endif // WALKING_STATE_H