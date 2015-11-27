#include "StunState.h"

#include "TestPlayerStates.h"

#include <iostream>

StunState::StunState()
	:firstUpdate_(true)
{
}


StunState::~StunState()
{
}

void StunState::onEnter(Player& player)
{
	firstUpdate_ = true;
}

void StunState::onExit(Player& player)
{
}

void StunState::handleInput(Player& player, SDL_Event& e)
{
}

void StunState::update(Player& player)
{
	if (!firstUpdate_)
	{
		if (!player.getComponent<PhysicsComponent>()->isFalling())
		{
			player.changeState(&states::airborneState);
			return;
		}
	}
	else
	{
		firstUpdate_ = false;
	}

}
