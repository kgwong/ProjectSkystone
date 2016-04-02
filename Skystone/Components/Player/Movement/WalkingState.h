#ifndef WALKING_STATE_H
#define WALKING_STATE_H

#include "PlayerState.h"
#include "GameTypes/Direction.h"

class WalkingState : public PlayerState
{
public:
	static const float JUMP_VELOCITY;
	static const float WALK_VELOCITY;

public:
	WalkingState();
	virtual ~WalkingState();

	virtual void onEnter(Scene& scene, GameObject& player);
	virtual void onExit(Scene& scene, GameObject& player);
	virtual void handleInput(Scene& scene, GameObject& player, SDL_Event& e);
	virtual void update(Scene& scene, GameObject& player);

	virtual std::string name() { return "Walking"; }
};

#endif // WALKING_STATE_H