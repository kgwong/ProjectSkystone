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
	if (scene.gameObjects.playerHook != nullptr)
	{
		scene.gameObjects.playerHook->kill();
		scene.gameObjects.playerHook = nullptr;
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

	//if LAUNCH_HOOK button is released
	//switch state to LAUNCH STATE.
	if (GameInputs::keyDown(e,ControlType::LAUNCH_HOOK)) //if (GameInputs::keyUp(e, ControlType::LAUNCH_HOOK))
	{
		//states need to also pass the reference to the hook here.
		LOG("FLAPJACKS") << owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name();
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookLaunchState");
	}
}
void HookDisconnectState::update(Scene& scene)
{
	/*if (player.getComponent<PlayerControlComponent>()->HookState().hookRef != nullptr)
	{
		player.getComponent<PlayerControlComponent>()->HookState().hookRef->kill();
		player.getComponent<PlayerControlComponent>()->HookState().hookRef = nullptr;
	}*/
}

AimState& HookDisconnectState::getAimState()
{
	return playerAim_;
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

