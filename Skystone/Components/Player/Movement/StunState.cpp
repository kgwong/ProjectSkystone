#include "StunState.h"

#include "PlayerMovementState.h"
#include "GameObject/GameObject.h"
#include "Components/Player/PlayerControlComponent.h"

StunState::StunState()
	:firstUpdate_(true)
{
}


StunState::~StunState()
{
}

void StunState::onEnter(Scene& scene, GameObject& player)
{
	firstUpdate_ = true;
}

void StunState::onExit(Scene& scene, GameObject& player)
{
}

void StunState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{
}

void StunState::update(Scene& scene, GameObject& player)
{
	if (!firstUpdate_)
	{
		if (!player.getComponent<PhysicsComponent>()->isFalling())
		{
			//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
			player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::airborneState);
			return;
		}

		if (player.getComponent<PlayerControlComponent>()->HookState().hanging)
		{
			player.getComponent<PlayerControlComponent>()->HookState().setHanging(false);
			player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::airborneState);
			player.getComponent<PhysicsComponent>()->enableGravity(true);
			return;
		}

		if (!player.getComponent<PlayerControlComponent>()->HookState().hanging)
		{
			return;
		}
	}
	else
	{
		firstUpdate_ = false;
	}

}
