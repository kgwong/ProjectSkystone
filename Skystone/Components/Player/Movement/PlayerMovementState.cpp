#include "PlayerMovementState.h"

#include "PlayerState.h"
#include "Application/Log.h"

#include "ComponentEvents/CollisionEvent.h" 
#include "Game/GameConstants.h"

WalkingState PlayerMovementState::walkingState;
FlyingState PlayerMovementState::flyingState;
AirborneState PlayerMovementState::airborneState;
StunState PlayerMovementState::stunState;
HangState PlayerMovementState::hangState;
LaunchState PlayerMovementState::launchState;

PlayerMovementState::PlayerMovementState(GameObject& owner)
	: InputComponent(owner), 
	currentState_(&PlayerMovementState::airborneState)
{
	LOG("FLAPJACKS") << "HI";
	canSwing = true;
	direction = 0;
}

PlayerMovementState::~PlayerMovementState()
{
}

void PlayerMovementState::handleInput(Scene& scene, SDL_Event& e)
{
	currentState_->handleInput(scene, owner_, e);
}

void PlayerMovementState::update(Scene& scene)
{
	currentState_->update(scene,owner_);
	//LOG("INFO") << currentState_->name();
	canSwing = true;
}

void PlayerMovementState::changeState(Scene& scene, PlayerState* state)
{
	currentState_->onExit(scene, owner_);
	currentState_ = state;
	currentState_->onEnter(scene, owner_);
}

PlayerState* PlayerMovementState::getState()
{
	return currentState_;
}

void PlayerMovementState::handleEvent(const CollisionEvent & e)
{
	//might not be in airborne state.
	if (currentState_ == &PlayerMovementState::hangState)
	{
		if (e.getOtherObject().getType() == GameObject::Type::TILE)
		{

			Point swingVector = hangState.SwingVector();
			//at the right edge of the tile or inside.
			if (swingVector.x >= e.getOtherObject().getPosX())
			{
				canSwing = false;
				Point offSet{e.getOtherObject().getPosX() + Constants::TILE_SIZE,e.getOtherObject().getPosY()};
				owner_.setPos(offSet);
			}
			else
			{
				canSwing = true;
			//	owner_.setPos(swingVector);
			}
		}
	}
}

void PlayerMovementState::setCanSwing(bool swing)
{
	canSwing = swing;
}

void PlayerMovementState::setDirection(int dir)
{
	direction = dir;
}

