#include "HookLaunchState.h"

#include "PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "Components/Common/StickOnCollision.h"

HookLaunchState::HookLaunchState()
{
}

HookLaunchState::~HookLaunchState()
{
}

void HookLaunchState::onEnter(Scene& scene, GameObject& player)
{
	//player.getComponent<PlayerHookState>()->instantiateHook();
	//float testvel = 5.0f;
	//auto physics = player.getComponent<PlayerHookState>()->hookRef->getComponent<PhysicsComponent>();
	//physics->setVelX(testvel * 60.0f);
	//physics->setVelY(testvel * 60.0f);
}

void HookLaunchState::onExit(Scene& scene, GameObject& player)
{
	//set hook's x and y velocity to zero
	//if connectstate.. do not destroy hook
	//if disconnect state destroy hook.
}

void HookLaunchState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{
	//if hook is launched already, and key is pressed again, switch to disconnect state.
	//if (GameInputs::keyDown(e, LAUNCH_HOOK))
	//{
	//	player.getComponent<PlayerControlComponent>()->changeHookState(scene, &PlayerHookState::disconnectState);
	//}

	//or to be simple do nothing.
}

//change player to hook.
void HookLaunchState::update(Scene& scene, GameObject& player)
{
	//hook shots can be interrupted by enemy touching u
	if (player.getComponent<PlayerControlComponent>()->MovementState().getState() == &PlayerMovementState::stunState)
	{
		player.getComponent<PlayerControlComponent>()->HookState().changeState(scene, &PlayerHookState::disconnectState);
		return;
	}

	if (player.getComponent<PlayerControlComponent>()->HookState().hookRef == nullptr)
	{
		player.getComponent<PlayerControlComponent>()->HookState().changeState(scene, &PlayerHookState::disconnectState);
		return;
	}
	else
	{
		//create out of bounds function.
		LOG("INFO") << player.getComponent<PlayerControlComponent>()->HookState().hookRef->getPos();
	}

	if (player.getComponent<PlayerControlComponent>()->MovementState().getState() == &PlayerMovementState::hangState)
	{
		player.getComponent<PlayerControlComponent>()->MovementState().changeState(scene,&PlayerMovementState::airborneState);
	}

	//StickOnCollision* hook_collision = nullptr;
	//auto control = player.getComponent<PlayerControlComponent>();
	//if (player.getComponent<PlayerControlComponent>()->HookState().hookRef != nullptr)
	//	hook_collision = control->HookState().hookRef->getComponent<StickOnCollision>();

	//if (hook_collision != nullptr)
	//{
	//	if (hook_collision->isConnected)
	//	{
	//		auto localref = control->HookState().hookRef;
	//		localref->getComponent<PhysicsComponent>()->setVelX(0.0f);
	//		localref->getComponent<PhysicsComponent>()->setVelY(0.0f);
	//		control->HookState().setHanging(true);
	//	}

	//}
}

double HookLaunchState::getAngle()
{
	return 0.0;
}

