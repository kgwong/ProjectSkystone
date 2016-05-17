#include "HookLaunchState.h"

#include "PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "Components/Common/StickOnCollision.h"
#include "GameMath/CircleMath.h"

HookLaunchState::HookLaunchState(GameObject& owner)
	: HookStateManager(owner)
{
}

HookLaunchState::~HookLaunchState()
{
}

void HookLaunchState::onEnter(Scene& scene)
{
	instantiateHook(scene);
}

void HookLaunchState::onExit(Scene& scene)
{
	//set hook's x and y velocity to zero
	//if connectstate.. do not destroy hook
	//if disconnect state destroy hook.
}

void HookLaunchState::handleInput(Scene& scene, SDL_Event& e)
{
	//if hook is launched already, and key is pressed again, switch to disconnect state.
	//if (GameInputs::keyDown(e, LAUNCH_HOOK))
	//{
	//	player.getComponent<PlayerControlComponent>()->changeHookState(scene, &PlayerHookState::disconnectState);
	//}

	//or to be simple do nothing.
}


void HookLaunchState::instantiateHook(Scene& scene)
{
	int test_velocity = 5;
	_degrees = owner_.getComponent<PlayerControlComponent>()->HookState().getDegrees();
	float leftSideDegree = 225;
	float rightSideDegree = 315;
	float upSideDegree = 270;

	Point hookPosition = scene.gameObjects.getPlayer().getPos();

	//offset.
	if (_degrees == leftSideDegree)
		hookPosition.x -= 20;
	else if (_degrees == rightSideDegree)
		hookPosition.x += 30;
	else if (_degrees == upSideDegree)
		hookPosition.y -= 50;

	scene.gameObjects.playerHook = scene.gameObjects.add("PlayerHook", "Player Hook", hookPosition);

	float testVel = 15.0f;
	float newVelX = (float)(testVel * cos(toRadians(_degrees)));
	float newVelY = (float)(testVel * sin(toRadians(_degrees)));
	scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->enableGravity(false);
	scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->setVelX(newVelX * 60.0f);
	scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->setVelY(newVelY * 60.0f);
}

//change player to hook.
void HookLaunchState::update(Scene& scene)
{
	//hook shots can be interrupted by enemy touching u
	if (owner_.getComponent<PlayerControlComponent>()->MovementState().getState()->name() == "StunState")
	{
		owner_.getComponent<PlayerControlComponent>()->HookState().changeState(scene, "HookDisconnectState");
		return;
	}

	// owner_.getComponent<PlayerControlComponent>()->HookState() 
	//returns nullptr when HookState() returns by reference. 
	//Currently returns HookState copy, so hookRef is not null or some reason
	//this makes no sense, you normally want to return my reference since there's no 
	//reason to copy your state object... is there?
	if (scene.gameObjects.playerHook == nullptr)
	{
		owner_.getComponent<PlayerControlComponent>()->HookState().changeState(scene, "HookDisconnectState");
		return;
	}
	else
	{
		//create out of bounds function.
		//LOG("INFO") << player.getComponent<PlayerControlComponent>()->HookState().hookRef->getPos();
	}

	if (owner_.getComponent<PlayerControlComponent>()->MovementState().getState()->name() == "Hang")
	{
		owner_.getComponent<PlayerControlComponent>()->MovementState().changeState(scene, "AirborneState");
	}

	auto hook_collision = scene.gameObjects.playerHook->getComponent<StickOnCollision>();
	if (hook_collision != nullptr)
	{
		if (hook_collision->isConnected)
		{
			owner_.getComponent<PlayerControlComponent>()->HookState().changeState(scene, "HookConnectState");
		}
	}
}

double HookLaunchState::getAngle()
{
	return 0.0;
}

std::string HookLaunchState::name()
{
	return "HookLaunchState"; 
}

