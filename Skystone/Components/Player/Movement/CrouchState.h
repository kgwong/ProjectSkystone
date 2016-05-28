#ifndef CROUCH_STATE_H
#define CROUCH_STATE_H

#include "PlayerState.h"

class PlayerControlComponent;
class ControlComponent;
class ColliderComponent;
class PhysicsComponent;

class CrouchState : public PlayerState
{
public:
	CrouchState(GameObject& owner);
	virtual ~CrouchState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);

	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	virtual void start(Scene& scene);

	virtual std::string name();

private:
	PlayerControlComponent* controlComponent_;
	ColliderComponent* collider_;
	PhysicsComponent* physics_;
};

#endif //CROUCH_STATE_H
