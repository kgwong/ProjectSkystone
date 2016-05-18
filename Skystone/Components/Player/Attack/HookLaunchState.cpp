#include "HookLaunchState.h"

#include "PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "Components/Common/StickOnCollision.h"
#include "Components/Collider/ColliderComponent.h"
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
}

void HookLaunchState::handleInput(Scene& scene, SDL_Event& e)
{
}


void HookLaunchState::instantiateHook(Scene& scene)
{
	int test_velocity = 5;
	_degrees = owner_.getComponent<PlayerControlComponent>()->HookState().getDegrees();
	float leftSideDegree = 225;
	float rightSideDegree = 315;
	float upSideDegree = 270;

	Point hookPosition = scene.gameObjects.getPlayer().getPos();

	////offset.
	if (_degrees == leftSideDegree)
		hookPosition.x -= 20;
	else if (_degrees == rightSideDegree)
		hookPosition.x += 30;
	else if (_degrees == upSideDegree)
		hookPosition.y -= 50;

	//check to see if the hook is spawned inside of a tile.
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

	auto hook_collision = scene.gameObjects.playerHook->getComponent<StickOnCollision>();
	if (hook_collision != nullptr && hook_collision->isConnected)
	{
		owner_.getComponent<PlayerControlComponent>()->HookState().changeState(scene, "HookConnectState");
	}
	//if hooks velocity is 0, set the player's hookstate to disconnect
	else if (scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->getVelX() == 0 && scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->getVelY() == 0)
	{
		owner_.getComponent<PlayerControlComponent>()->HookState().changeState(scene, "HookDisconnectState");
	}
	//hook shots can be interrupted by enemy touching u
	else if (owner_.getComponent<PlayerControlComponent>()->MovementState().getState()->name() == "StunState")
	{
		owner_.getComponent<PlayerControlComponent>()->HookState().changeState(scene, "HookDisconnectState");
	}

	if (scene.gameObjects.playerHook == nullptr || !scene.gameObjects.playerHook->getPos().inBounds(scene.getWidth(), scene.getHeight()))
	{
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookDisconnectState");
	}

	if (owner_.getComponent<PlayerControlComponent>()->MovementState().getState()->name() == "Hang")
	{
		owner_.getComponent<PlayerControlComponent>()->MovementState().changeState(scene, "AirborneState");
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

