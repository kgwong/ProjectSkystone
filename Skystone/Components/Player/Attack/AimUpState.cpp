#include "AimUpState.h"

#include "PlayerAttackState.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"
#include "Resources/Resources.h"

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
	LOG("Kevin") << "AimUpEnter";
	dir_ = AimUpState::Direction::NONE;
	renderer_->setSprite("Images/idle cycle.png");
}

void AimUpState::onExit(Scene & scene)
{
	LOG("Kevin") << "AimUpExit";
}

void AimUpState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, UP))
	{
		controlComponent_->changeAttackState(scene, "DefaultAimState");
	}
	if (GameInputs::keyDown(e, LEFT))
	{
		dir_ = AimUpState::Direction::LEFT;
		LOG("Kevin") << "test";
		renderer_->setSprite("Images/fire cycle standing.png");
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

void AimUpState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
	renderer_ = owner_.getComponent<SpriteRenderer>();
}

void AimUpState::update(Scene& scene)
{
	if (dir_ != AimUpState::Direction::NONE)
	{
		physics_->setVelX(0);
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

