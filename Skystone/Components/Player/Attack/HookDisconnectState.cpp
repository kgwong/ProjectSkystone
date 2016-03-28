#include "HookDisconnectState.h"
#include "StickOnCollision.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

HookDisconnectState::HookDisconnectState()
{
}


HookDisconnectState::~HookDisconnectState()
{
}

void HookDisconnectState::onEnter(GameObject& player)
{
	//default state. ~ problem shared_ptr is empty.
	//if hook not deleted or gravity not restored.. do it here.
	//player.getComponent<PlayerHookState>()->hookRef;
	//if (player.getComponent<PlayerHookState>()->hookRef != nullptr)
	//{
	//	player.getComponent<PlayerHookState>()->hookRef->disownComponents();
	//	player.getComponent<PlayerHookState>()->hookRef = nullptr;
	//}
}
void HookDisconnectState::onExit(GameObject& player)
{
	//goes to launch state... prepare for that. do nothing.
}
void HookDisconnectState::handleInput(GameObject& player, SDL_Event& e)
{
	//if LAUNCH_HOOK button is released
	//switch state to LAUNCH STATE.
	if (GameInputs::keyDown(e, ControlType::LAUNCH_HOOK))
	{
		//states need to also pass the reference to the hook here.
		player.getComponent<PlayerControlComponent>()->changeHookState(&PlayerHookState::launchState);
		
	}
}
void HookDisconnectState::update(GameObject& player) 
{
	//check here when to switch to launch state.
}

double HookDisconnectState::getAngle() 
{
	//obtains angle of where hook was launched relative to player.
	return 0.0;
}

