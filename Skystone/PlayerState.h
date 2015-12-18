#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <SDL/SDL.h>
#include <string>
#include "Controls.h"

#include "GameObject.h"
#include "PhysicsComponent.h"

class PlayerState
{
public:
	virtual void onEnter(GameObject& player) = 0;
	virtual void onExit(GameObject& player) = 0;
	virtual void handleInput(GameObject& player, SDL_Event& e) = 0;
	virtual void update(GameObject& player) = 0;

	virtual std::string name() = 0;

};

#endif //PLAYER_STATE_H