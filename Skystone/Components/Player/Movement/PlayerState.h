#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <SDL/SDL.h>
#include <string>
#include "Game/GameInputs.h"

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

	//adding these!!! ~ make these their own components.
	//virtual void onEnter(Scene& scene) = 0;
	//virtual void onExit(Scene& scene) = 0;
	//virtual void handleInput(Scene& scene, SDL_Event& e) = 0;
	//virtual void update(Scene& scene) = 0;

};

#endif //PLAYER_STATE_H