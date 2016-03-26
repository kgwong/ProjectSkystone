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

void HookConnectState::onEnter(GameObject& player)
{
	//hook
	//set x and y velocity to zero if not done.
	//player
	//set x and y velocity of player also to zero.
	//set gravity to false

	//std::shared_ptr<GameObject> localHook = player.getComponent<PlayerHookState>()->hookRef;
	//PhysicsComponent* physics = localHook->getComponent<PhysicsComponent>();
	//physics->setVelX(0.0f);
	//physics->setVelY(0.0f);
}
void HookConnectState::onExit(GameObject& player) 
{
	//player
	//set gravity to true

	//hook is killed after exit.
}
void HookConnectState::handleInput(GameObject& player, SDL_Event& e)
{
	//player controls
	//if player moves left, swings left.
	//if player moves right, swings right.
	

	//use formula y = center of y + cos(currentAngle) * radius;
				//x = center of x + sin(currentAngle) * radius;
	//formula is inverted because of how rotations work in sdl.

	//use GameInputs::keyDown and keyHeld for acceleration!!
	//longer the button is held the faster the player swings.
	//change in velocity.

	if (GameInputs::keyDown(e, LAUNCH_HOOK))
	{
		player.getComponent<PlayerControlComponent>()->changeHookState(&PlayerHookState::disconnectState);
	}

}
void HookConnectState::update(GameObject& player)
{
	//handle change in velocity here
	//auto playerPhysics = player.getComponent<PhysicsComponent>();
	//LOG("INFO") << playerPhysics->getVelX() << ", " << playerPhysics->getVelY();
}

double HookConnectState::getAngle()
{
	//record player's angle relative to the pivot.
	return 0.0; 
}

