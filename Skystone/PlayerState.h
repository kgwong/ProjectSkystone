#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <SDL/SDL.h>
#include <string>
#include "Controls.h"

#include "Player.h"
#include "PhysicsComponent.h"

class PlayerState
{
public:
	virtual void onEnter(Player& player) = 0;
	virtual void onExit(Player& player) = 0;
	virtual void handleInput(Player& player, SDL_Event& e) = 0;
	virtual void update(Player& player) = 0;

	virtual std::string name() = 0;

};

#endif //PLAYER_STATE_H