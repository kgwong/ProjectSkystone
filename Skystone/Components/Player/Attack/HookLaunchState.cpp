#include "HookLaunchState.h"

#include "PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "Components/Common/StickOnCollision.h"
#include "Components/Collider/ColliderComponent.h"
#include "GameMath/CircleMath.h"
#include "Components/Tile/TileComponent.h"
#include "Game/GameConstants.h"

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
	degrees_ = owner_.getComponent<PlayerControlComponent>()->HookState().getDegrees();
	float leftSideDegree = 225;
	float rightSideDegree = 315;
	float upSideDegree = 270;

	Point hookPosition = scene.gameObjects.getPlayer().getPos();

	////offset.
	if (degrees_ == leftSideDegree)
		hookPosition.x -= Constants::TILE_SIZE;
	else if (degrees_ == rightSideDegree)
		hookPosition.x += Constants::TILE_SIZE;
	else if (degrees_ == upSideDegree)
		hookPosition.y -= Constants::TILE_SIZE;
	float frow = hookPosition.y / Constants::TILE_SIZE;
	float fcol = hookPosition.x / Constants::TILE_SIZE;
	int row = (int)roundf(frow);
	int col = (int)roundf(fcol);
	if (row < 0 || row >= scene.gameObjects.getTiles().rows)
	{
		LOG("HARVEY") << "ROW OUT OF BOUNDS";
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookDisconnectState");
		return;
	}
	if (col < 0 || col >= scene.gameObjects.getTiles().cols)
	{
		LOG("HARVEY") << "COL OUT OF BOUNDS";
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookDisconnectState");
		return;
	}

	TileComponent::Type tileType = scene.gameObjects.getTiles().tiles[row][col].getComponent<TileComponent>()->getTileType();
	if (tileType == TileComponent::Type::EMPTY)
	{
		scene.gameObjects.playerHook = scene.gameObjects.add("PlayerHook", "Player Hook", hookPosition);
		float testVel = 15.0f;
		float newVelX = (float)(testVel * cos(toRadians(degrees_)));
		float newVelY = (float)(testVel * sin(toRadians(degrees_)));
		scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->enableGravity(false);
		scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->setVelX(newVelX * 60.0f);
		scene.gameObjects.playerHook->getComponent<PhysicsComponent>()->setVelY(newVelY * 60.0f);
	}
	else
	{
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookDisconnectState");
	}
}

void HookLaunchState::handleEvent(const CollisionEvent& e)
{
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
	//hook shots can be interrupted by enemy touching you
	else if (owner_.getComponent<PlayerControlComponent>()->MovementState().getState()->name() == "StunState")
	{
		owner_.getComponent<PlayerControlComponent>()->HookState().changeState(scene, "HookDisconnectState");
	}

	//if hook out of bounds or hook is not spawned, goto hookdisconnectstate.
	if (scene.gameObjects.playerHook == nullptr || !scene.gameObjects.playerHook->getPos().inBounds(scene.getWidth(), scene.getHeight()))
	{
		owner_.getComponent<PlayerControlComponent>()->changeHookState(scene, "HookDisconnectState");
	}

	if (owner_.getComponent<PlayerControlComponent>()->MovementState().getState()->name() == "Hang")
	{
		//create substates for airborne state.
		//1. jump
		//2. falling
		//3. hanging
		owner_.getComponent<PlayerControlComponent>()->MovementState().changeState(scene, "AirborneState");
	}

}


std::string HookLaunchState::name()
{
	return "HookLaunchState"; 
}

