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
	
	direction_ = 0;
	direction_ = owner_.getComponent<PlayerControlComponent>()->MovementState().direction;
	//LOG("INFO") << "direction: " << direction_;
	if (direction_ > 0)
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(5.0f * 60.0f);
		owner_.getComponent<PhysicsComponent>()->setVelY(5.0f * -60.0f);
		LOG("HARVEY") << "DIRECTION IS: " << direction_;
	}
	else if (direction_ < 0)
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(5.0f * -60.0f);
		owner_.getComponent<PhysicsComponent>()->setVelY(5.0f * -60.0f);
		LOG("HARVEY") << "direction is " << direction_;
	}
	else
	{
		LOG("HARVEY") << "DDirection is " << direction_;
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
		auto playerPhysics = owner_.getComponent<PhysicsComponent>();
		playerPhysics->enableGravity(true);
		if (!owner_.getComponent<PhysicsComponent>()->isFalling())
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		}
	}
	else
	{
		someSwitch_ = false;
	}
}
