#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <SDL/SDL.h>
#include <string>
#include "Game/Controls.h"

#include "GameObject/GameObject.h"
#include "Components/Physics/PhysicsComponent.h"

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