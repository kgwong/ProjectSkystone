#ifndef AIRBORNE_STATE_H
#define AIRBORNE_STATE_H

#include "PlayerState.h"

class AirborneState : public PlayerState
{
public:
	AirborneState();
	virtual ~AirborneState();

	virtual void onEnter(GameObject& player);
	virtual void onExit(GameObject& player);
	virtual void handleInput(GameObject& player, SDL_Event& e);
	virtual void update(GameObject& player);


	virtual std::string name() { return "Airborne"; }

private:
	bool jumpHeld_;

};

#endif //AIRBORNE_STATE_H