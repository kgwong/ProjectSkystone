#ifndef LOCK_MOVEMENT_STATE_H
#define LOCK_MOVEMENT_STATE_H

#include "PlayerState.h"

class PlayerControlComponent;
class PhysicsComponent;

class LockMovementState : public PlayerState
{
public:
	LockMovementState(GameObject& owner);
	virtual ~LockMovementState();

	virtual void onEnter(Scene& scene);
	//virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual std::string name();

private:
	PlayerControlComponent* controlComponent_;
	PhysicsComponent* physics_;

};

#endif //LOCK_MOVEMENT_STATE_H