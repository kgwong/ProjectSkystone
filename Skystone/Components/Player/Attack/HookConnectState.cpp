#include "HookConnectState.h"
#include "PlayerHookState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

HookConnectState::HookConnectState()
{
}


HookConnectState::~HookConnectState()
{
}

void HookConnectState::onEnter(Scene& scene, GameObject& player)
{
	//player.getComponent<PlayerControlComponent>()->MovementState().changeState(&PlayerMovementState::hangState);
}
void HookConnectState::onExit(Scene& scene, GameObject& player) 
{
	//player
	//set gravity to true

	//hook is killed after exit.
}
void HookConnectState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{
	if (GameInputs::keyUp(e, LAUNCH_HOOK))
	{
		player.getComponent<PlayerControlComponent>()->changeHookState(scene, &PlayerHookState::disconnectState);
		player.getComponent<PlayerControlComponent>()->HookState().setHanging(false);
		player.getComponent<PhysicsComponent>()->enableGravity(true);
	}

}
void HookConnectState::update(Scene& scene, GameObject& player)
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

