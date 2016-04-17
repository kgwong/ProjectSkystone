#ifndef FLYING_STATE_H
#define FLYING_STATE_H

#include "PlayerState.h"

class PlayerControlComponent;
class PhysicsComponent;
class SpriteRenderer;

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

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual std::string name() { return "FlyingState"; }

private:
	PlayerControlComponent* controlComponent_;
	PhysicsComponent* physics_;
	SpriteRenderer* renderer_;
};

#endif //FLYING_STATE_H