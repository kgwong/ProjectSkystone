#include "HookDisconnectState.h"
#include "Components/Common/StickOnCollision.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

HookDisconnectState::HookDisconnectState()
{
}


HookDisconnectState::~HookDisconnectState()
{
}

void HookDisconnectState::onEnter(Scene& scene, GameObject& player)
{
	if (player.getComponent<PlayerControlComponent>()->HookState().hookRef != nullptr)
	{
		player.getComponent<PlayerControlComponent>()->HookState().hookRef->kill();
		player.getComponent<PlayerControlComponent>()->HookState().hookRef = nullptr;
	}
}
void HookDisconnectState::onExit(Scene& scene, GameObject& player)
{
	//goes to launch state... prepare for that. do nothing.
}
void HookDisconnectState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{
	//if LAUNCH_HOOK button is released
	//switch state to LAUNCH STATE.
	if (GameInputs::keyDown(e, ControlType::LAUNCH_HOOK))
	{
		//states need to also pass the reference to the hook here.
		player.getComponent<PlayerControlComponent>()->changeHookState(scene, &PlayerHookState::launchState);
		LOG("INFO") << player.getComponent<PlayerControlComponent>()->HookState().getState()->name();
	}
}
void HookDisconnectState::update(Scene& scene, GameObject& player)
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

