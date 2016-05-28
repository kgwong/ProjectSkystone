#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "PlayerState.h"

class PlayerControlComponent;

class IdleState : public PlayerState
{
public:
	IdleState(GameObject& owner);
	virtual ~IdleState();

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

#endif //IDLE_STATE_H
