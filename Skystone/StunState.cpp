#include "StunState.h"

#include "PlayerMovementState.h"
#include "GameObject.h"
#include "PlayerControlComponent.h"

StunState::StunState()
	:firstUpdate_(true)
{
}


StunState::~StunState()
{
}

void StunState::onEnter(GameObject& player)
{
	firstUpdate_ = true;
}

void StunState::onExit(GameObject& player)
{
}

void StunState::handleInput(GameObject& player, SDL_Event& e)
{
}

void StunState::update(GameObject& player)
{
	if (!firstUpdate_)
	{
		if (!player.getComponent<PhysicsComponent>()->isFalling())
		{
			//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
			player.getComponent<PlayerControlComponent>()->changeMovementState(&PlayerMovementState::airborneState);
			return;
		}
	}
	else
	{
		firstUpdate_ = false;
	}

}
