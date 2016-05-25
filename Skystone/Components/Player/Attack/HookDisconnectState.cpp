#include "HookDisconnectState.h"
#include "Components/Common/StickOnCollision.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

HookDisconnectState::HookDisconnectState(GameObject& owner)
	: HookStateManager(owner)
{
}


HookDisconnectState::~HookDisconnectState()
{
}

void HookDisconnectState::onEnter(Scene& scene)
{
	degrees_ = 0.0f;
	playerAim_ = AimState::UP;
	disconnectHook(scene);
	
	if (owner_.getComponent<PlayerControlComponent>()->MovementState().getState()->name() == "SwingState")
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
	}
}
void HookDisconnectState::onExit(Scene& scene)
{
}
void HookDisconnectState::handleInput(Scene& scene, SDL_Event& e)
{
	
	if (GameInputs::keyDown(e, UP))
	{
		playerAim_ = AimState::UP;
	}
	else if (GameInputs::keyDown(e, LEFT))
	{
		playerAim_ = AimState::LEFT;
	}
	else if (GameInputs::keyDown(e, RIGHT))
	{
		playerAim_ = AimState::RIGHT;
	}

	if (GameInputs::keyDown(e,ControlType::LAUNCH_HOOK))
	{
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookLaunchState");
	}
}
void HookDisconnectState::update(Scene& scene)
{
}

AimState& HookDisconnectState::getAimState()
{
	return playerAim_;
}

void HookDisconnectState::setAimState(AimState aim)
{
	playerAim_ = aim;
}

float HookDisconnectState::getDegrees()
{
	switch (playerAim_)
	{
	case AimState::UP:
		degrees_ = 270;
		break;
	case AimState::LEFT:
		degrees_ = 225;
		break;
	case AimState::RIGHT:
		degrees_ = 315;
		break;
	default:
		degrees_ = 270;
	}

	return degrees_;
}

void HookDisconnectState::disconnectHook(Scene& scene)
{
	if (scene.gameObjects.playerHook != nullptr)
	{
		scene.gameObjects.playerHook->kill();
		scene.gameObjects.playerHook = nullptr;
	}
}

std::string HookDisconnectState::name()
{
	return "HookDisconnectState"; 
}

