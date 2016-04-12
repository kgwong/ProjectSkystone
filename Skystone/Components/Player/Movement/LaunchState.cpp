#include "LaunchState.h"

#include "PlayerMovementState.h"
#include "GameObject/GameObject.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

LaunchState::LaunchState(GameObject& owner)
	:PlayerState(owner)
{
	someSwitch_ = true;
}

LaunchState::~LaunchState()
{
}

void LaunchState::onEnter(Scene& scene)
{
	someSwitch_ = true;
	//hack -- Kevin
	direction_ = owner_.getComponent<PlayerControlComponent>()->MovementState().hangState.getDirection();
	
	//LOG("INFO") << "direction: " << direction_;
	if (direction_ > 0)
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(5.0f * 60.0f);
		owner_.getComponent<PhysicsComponent>()->setVelY(5.0f * -60.0f);
	}
	else if (direction_ < 0)
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(5.0f * -60.0f);
		owner_.getComponent<PhysicsComponent>()->setVelY(5.0f * -60.0f);
	}
	else
	{
		LOG("FLAPJACKS") << "direction is " << direction_;
	}
}

void LaunchState::onExit(Scene& scene)
{
	owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(0);
}

void LaunchState::handleInput(Scene& scene, SDL_Event& e)
{

}

void LaunchState::update(Scene& scene)
{
	if (!someSwitch_)
	{
		if (!owner_.getComponent<PhysicsComponent>()->isFalling())
		{
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
	}
	else
	{
		someSwitch_ = false;
	}
}
