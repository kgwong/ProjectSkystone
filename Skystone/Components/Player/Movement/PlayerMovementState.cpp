#include "PlayerMovementState.h"

#include "PlayerState.h"
#include "Application/Log.h"

#include "ComponentEvents/CollisionEvent.h" 

#include <cassert>

PlayerMovementState::PlayerMovementState(GameObject& owner)
	: InputComponent(owner),
	walkingState(owner),
	flyingState(owner),
	airborneState(owner),
	stunState(owner),
	hangState(owner),
	launchState(owner),
	currentState_(&airborneState)
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
	currentState_->handleInput(scene, e);
}

void PlayerMovementState::start(Scene& scene)
{
	walkingState.start(scene);
	flyingState.start(scene);
	airborneState.start(scene);
	stunState.start(scene);
	hangState.start(scene);
	launchState.start(scene);
}

void PlayerMovementState::update(Scene& scene)
{
	currentState_->update(scene);
	//LOG("INFO") << currentState_->name();
	canSwing = true;
}

void PlayerMovementState::changeState(Scene& scene, const std::string& stateName)
{
	currentState_->onExit(scene);
	currentState_ = getStateFromName(stateName);
	currentState_->onEnter(scene);
}

PlayerState* PlayerMovementState::getState()
{
	return currentState_;
}

void PlayerMovementState::handleEvent(const CollisionEvent & e)
{
	//might not be in airborne state.
	if (currentState_->name() == "Hang")
	{
		if (e.getOtherObject().getType() == GameObject::Type::TILE)
		{

			Point swingVector = hangState.SwingVector();
			//at the right edge of the tile or inside.
			if (swingVector.x >= e.getOtherObject().getPosX())
			{
				canSwing = false;
				Point offSet{e.getOtherObject().getPosX() + 32,e.getOtherObject().getPosY()};
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

PlayerState* PlayerMovementState::getStateFromName(const std::string& name)
{
	if (name == walkingState.name())
	{
		return &walkingState;
	}
	else if (name == flyingState.name())
	{
		return &flyingState;
	}
	else if (name == airborneState.name())
	{
		return &airborneState;
	}
	else if (name == stunState.name())
	{
		return &stunState;
	}
	else if (name == hangState.name())
	{
		return &hangState;
	}
	else if (name == launchState.name())
	{
		return &launchState;
	}
	else
	{
		LOG("ERROR") << "Unknown state";
		assert(false);
		return nullptr;
	}
}

