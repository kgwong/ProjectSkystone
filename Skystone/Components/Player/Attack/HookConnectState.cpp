#include "HookConnectState.h"
#include "PlayerHookState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Common/StickOnCollision.h"
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
	connectHook(scene);
}
void HookConnectState::onExit(Scene& scene) 
{
	//player
	//set gravity to true

	//hook is killed after exit.
}
void HookConnectState::handleInput(Scene& scene, SDL_Event& e)
{
	//may change to using 2 different controls for launching hook and disconnecting.
	if (GameInputs::keyUp(e, LAUNCH_HOOK))
	{
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookDisconnectState");
		owner_.getComponent<PhysicsComponent>()->enableGravity(true);
	}

}
void HookConnectState::update(Scene& scene)
{
}

double HookConnectState::getAngle()
{
	//record player's angle relative to the pivot.
	return 0.0; 
}

void HookConnectState::connectHook(Scene& scene)
{
	StickOnCollision* hook_collision = nullptr;
	if (scene.gameObjects.playerHook != nullptr)
		hook_collision = scene.gameObjects.playerHook->getComponent<StickOnCollision>();

	if (hook_collision != nullptr)
	{
		if (hook_collision->isConnected)
		{
			scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->setVelX(0.0f);
			scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->setVelY(0.0f);
		}

	}
}

