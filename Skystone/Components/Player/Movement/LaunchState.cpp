#include "LaunchState.h"

#include "PlayerMovementState.h"
#include "GameObject/GameObject.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

LaunchState::LaunchState()
{
	someSwitch_ = true;
}

LaunchState::~LaunchState()
{
}

void LaunchState::onEnter(Scene& scene, GameObject& player)
{
	someSwitch_ = true;
	direction_ = PlayerMovementState::hangState.getDirection();
	
	//LOG("INFO") << "direction: " << direction_;
	if (direction_ > 0)
	{
		player.getComponent<PhysicsComponent>()->setVelX(5.0f * 60.0f);
		player.getComponent<PhysicsComponent>()->setVelY(5.0f * -60.0f);
	}
	else if (direction_ < 0)
	{
		player.getComponent<PhysicsComponent>()->setVelX(5.0f * -60.0f);
		player.getComponent<PhysicsComponent>()->setVelY(5.0f * -60.0f);
	}
	else
	{
		LOG("INFO") << "direction is " << direction_;
	}
}

void LaunchState::onExit(Scene& scene, GameObject& player)
{
	player.getComponent<PlayerControlComponent>()->MovementState().setDirection(0);
}

void LaunchState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{

}

void LaunchState::update(Scene& scene, GameObject& player)
{
	if (!someSwitch_)
	{
		if (!player.getComponent<PhysicsComponent>()->isFalling())
		{
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

		
	}
	else
	{
		someSwitch_ = false;
	}
}
