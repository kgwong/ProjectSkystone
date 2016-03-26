#include "HookLaunchState.h"

#include "PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "StickOnCollision.h"

HookLaunchState::HookLaunchState()
{
}

HookLaunchState::~HookLaunchState()
{
}

void HookLaunchState::onEnter(GameObject & player)
{
	//player.getComponent<PlayerHookState>()->instantiateHook();
	//float testvel = 5.0f;
	//auto physics = player.getComponent<PlayerHookState>()->hookRef->getComponent<PhysicsComponent>();
	//physics->setVelX(testvel * 60.0f);
	//physics->setVelY(testvel * 60.0f);
}

void HookLaunchState::onExit(GameObject & player)
{
	//set hook's x and y velocity to zero
	//if connectstate.. do not destroy hook
	//if disconnect state destroy hook.
}

void HookLaunchState::handleInput(GameObject & player, SDL_Event & e)
{
	//if hook is launched already, and key is pressed again, switch to disconnect state.
	if (GameInputs::keyDown(e, LAUNCH_HOOK))
	{
		player.getComponent<PlayerControlComponent>()->changeHookState(&PlayerHookState::disconnectState);
	}

	//or to be simple do nothing.
}

//change player to hook.
void HookLaunchState::update(GameObject & player)
{

	//using hook's stickOnCollision.... if it is connected 
	//change state to connectedState. ~ hacky stuff right now.
	//change into a raw ptr. hookRef
	//if (player.getComponent<PlayerHookState>()->hookRef != nullptr)
	//{
	//	std::shared_ptr<GameObject> localHookRef = player.getComponent<PlayerHookState>()->hookRef;
	//	StickOnCollision* stick_collision = localHookRef->getComponent<StickOnCollision>();
	//	if (stick_collision->isConnected)
	//		player.getComponent<PlayerControlComponent>()->changeHookState(&PlayerHookState::connectState);
	//}
}

double HookLaunchState::getAngle()
{
	return 0.0;
}

