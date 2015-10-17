#ifndef AIRBORNE_STATE_H
#define AIRBORNE_STATE_H

#include "PlayerState.h"

class AirborneState : public PlayerState
{
public:
	AirborneState();
	virtual ~AirborneState();

	virtual void onEnter(Player& player);
	virtual void onExit(Player& player);
	virtual void handleInput(Player& player, SDL_Event& e);
	virtual void update(Player& player);


	virtual std::string name() { return "Airborne"; }

private:
	bool jumpHeld_;

};

#endif //AIRBORNE_STATE_H