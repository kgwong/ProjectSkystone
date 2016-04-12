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
	if (owner_.getComponent<PlayerControlComponent>()->HookState().hookRef != nullptr)
	{
		owner_.getComponent<PlayerControlComponent>()->HookState().hookRef->kill();
		owner_.getComponent<PlayerControlComponent>()->HookState().hookRef = nullptr;
	}
}
void HookDisconnectState::onExit(Scene& scene)
{
	//goes to launch state... prepare for that. do nothing.
}
void HookDisconnectState::handleInput(Scene& scene, SDL_Event& e)
{
	//if LAUNCH_HOOK button is released
	//switch state to LAUNCH STATE.
	if (GameInputs::keyDown(e,ControlType::LAUNCH_HOOK) && GameInputs::keyHeld(ControlType::LAUNCH_HOOK)) //if (GameInputs::keyUp(e, ControlType::LAUNCH_HOOK))
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

double HookDisconnectState::getAngle() 
{
	//obtains angle of where hook was launched relative to player.
	return 0.0;
}

