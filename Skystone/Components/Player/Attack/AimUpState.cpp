#include "AimUpState.h"

#include "PlayerAttackState.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Application/Log.h"

AimUpState::AimUpState(GameObject& owner)
	:PlayerAimState(owner)
{
}


AimUpState::~AimUpState()
{
}

void AimUpState::onEnter(Scene& scene)
{
	dir_ = AimUpState::Direction::NONE;
}

void AimUpState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, UP))
	{
		//player.getComponent<PlayerAttackState>()->changeState(&PlayerAttackState::defaultAimState);
		owner_.getComponent<PlayerControlComponent>()->changeAttackState(scene, "DefaultAimState");
	}
	if (GameInputs::keyDown(e, LEFT))
	{
		dir_ = AimUpState::Direction::LEFT;
	}
	if (GameInputs::keyUp(e, LEFT))
	{
		dir_ = AimUpState::Direction::NONE;
	}
	if (GameInputs::keyDown(e, RIGHT))
	{
		dir_ = AimUpState::Direction::RIGHT;
	}
	if (GameInputs::keyUp(e, RIGHT))
	{
		dir_ = AimUpState::Direction::NONE;
	}

}

void AimUpState::update(Scene& scene)
{
	if (dir_ != AimUpState::Direction::NONE)
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(0);
	}
}

std::string AimUpState::name()
{
	return "AimUpState";
}

double AimUpState::getAngle()
{
	switch (dir_)
	{
	case AimUpState::Direction::LEFT:
		return 225;
	case AimUpState::Direction::RIGHT:
		return 315;
	default:
		return 270;
	}
}

