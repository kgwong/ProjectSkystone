#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <SDL/SDL.h>
#include <string>
#include "Game/GameInputs.h"

#include "GameObject/GameObject.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/InputComponent.h"

class PlayerState : public InputComponent
{
public:
	PlayerState(GameObject& owner);
	virtual ~PlayerState();

	virtual void onEnter(Scene& scene) {}
	virtual void onExit(Scene& scene) {}

	virtual std::string name() = 0;

};

#endif //PLAYER_STATE_H