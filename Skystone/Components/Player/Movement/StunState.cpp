#include "StunState.h"

#include "PlayerMovementState.h"
#include "GameObject/GameObject.h"
#include "Components/Player/PlayerControlComponent.h"

StunState::StunState(GameObject& owner)
	: PlayerState(owner), 
	firstUpdate_(true)
{
}


StunState::~StunState()
{
}

void StunState::onEnter(Scene& scene)
{
	firstUpdate_ = true;
}

void StunState::onExit(Scene& scene)
{
}

void StunState::handleInput(Scene& scene, SDL_Event& e)
{
}

void StunState::update(Scene& scene)
{
	if (!firstUpdate_)
	{
		if (!owner_.getComponent<PhysicsComponent>()->isFalling())
		{
			//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			return;
		}

		if (owner_.getComponent<PlayerControlComponent>()->HookState().hanging)
		{
			owner_.getComponent<PlayerControlComponent>()->HookState().setHanging(false);
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			owner_.getComponent<PhysicsComponent>()->enableGravity(true);
			return;
		}

		if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() != "HookConnectState")
		{
			owner_.getComponent<PlayerControlComponent>()->HookState().setHanging(false);
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			owner_.getComponent<PhysicsComponent>()->enableGravity(true);
			return;
		}

	}
	else
	{
		firstUpdate_ = false;
	}

}

std::string StunState::name()
{
	return "StunState";
}
