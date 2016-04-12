#include "HookConnectState.h"
#include "PlayerHookState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

HookConnectState::HookConnectState(GameObject& owner)
	:HookStateManager(owner)
{
}


HookConnectState::~HookConnectState()
{
}

void HookConnectState::onEnter(Scene& scene)
{
	//player.getComponent<PlayerControlComponent>()->MovementState().changeState(&PlayerMovementState::hangState);
}
void HookConnectState::onExit(Scene& scene) 
{
	//player
	//set gravity to true

	//hook is killed after exit.
}
void HookConnectState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, LAUNCH_HOOK))
	{
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookDisconnectState");
		owner_.getComponent<PlayerControlComponent>()->HookState().setHanging(false);
		owner_.getComponent<PhysicsComponent>()->enableGravity(true);
	}

}
void HookConnectState::update(Scene& scene)
{
	//if (player.getComponent<PlayerControlComponent>()->MovementState().getState() == &PlayerMovementState::hangState)
	//{
	//	player.getComponent<PhysicsComponent>()->enableGravity(false);
	//}

	//if (player.getComponent<PlayerControlComponent>()->HookState().getState() == &PlayerHookState::disconnectState)
	//{
	//	player.getComponent<PlayerControlComponent>()->HookState().setHanging(false);
	//	if (player.getComponent<PlayerControlComponent>()->HookState().hookRef != nullptr)
	//	{
	//		player.getComponent<PlayerControlComponent>()->HookState().hookRef->kill();
	//		player.getComponent<PlayerControlComponent>()->HookState().hookRef = nullptr;
	//	}
	//}
}

double HookConnectState::getAngle()
{
	//record player's angle relative to the pivot.
	return 0.0; 
}

