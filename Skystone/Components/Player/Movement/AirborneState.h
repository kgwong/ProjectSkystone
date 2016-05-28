#ifndef AIRBORNE_STATE_H
#define AIRBORNE_STATE_H

#include "PlayerState.h"

class PlayerControlComponent;
class PhysicsComponent;

class AirborneState : public PlayerState
{
public:
	AirborneState(GameObject& owner);
	virtual ~AirborneState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void handleEvent(const CollisionEvent& e);

	virtual void start(Scene& scene);
	virtual void update(Scene& scene);

	virtual std::string name();

private:
	PlayerControlComponent* controlComponent_;
	PhysicsComponent* physics_;

};

#endif //AIRBORNE_STATE_H