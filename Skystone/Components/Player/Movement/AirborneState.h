#ifndef AIRBORNE_STATE_H
#define AIRBORNE_STATE_H

#include "PlayerState.h"

class AirborneState : public PlayerState
{
public:
	AirborneState(GameObject& owner);
	virtual ~AirborneState();

	virtual void onEnter(Scene& scene);
	virtual void onExit(Scene& scene);
	virtual void handleInput(Scene& scene, SDL_Event& e);
	virtual void update(Scene& scene);

	virtual std::string name();

private:
	bool jumpHeld_;

};

#endif //AIRBORNE_STATE_H