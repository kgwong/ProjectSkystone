#ifndef WALKING_STATE_H
#define WALKING_STATE_H

#include "PlayerState.h"
#include "GameTypes/Direction.h"

class PlayerControlComponent;
class PhysicsComponent;

class WalkingState : public PlayerState
{
public:
	static const float JUMP_VELOCITY;
	static const float WALK_VELOCITY;

public:
	WalkingState(GameObject& owner);
	virtual ~WalkingState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual std::string name();

private:
	PlayerControlComponent* controlComponent_;
	PhysicsComponent* physics_;
};

#endif // WALKING_STATE_H