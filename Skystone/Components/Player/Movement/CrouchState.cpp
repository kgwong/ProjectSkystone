#include "CrouchState.h"

#include "../PlayerControlComponent.h"

#include "Components/Collider/ColliderComponent.h"

#include "Application/Log.h"

#include "Components/Physics/PhysicsComponent.h"

CrouchState::CrouchState(GameObject& owner)
	:PlayerState(owner)
{
}


CrouchState::~CrouchState()
{
}

void CrouchState::onEnter(Scene& scene)
{
	collider_->setHeight(32);
	collider_->setOffsetY(32);

	physics_->setVelX(0);
}

void CrouchState::onExit(Scene& scene)
{
	collider_->setHeight(64);
	collider_->setOffsetY(0);
}

void CrouchState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, DOWN))
	{
		controlComponent_->changeMovementState(scene, "IdleState");
	}
}

void CrouchState::update(Scene& scene)
{
}

void CrouchState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	collider_ = owner_.getComponent<ColliderComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
}

std::string CrouchState::name()
{
	return "CrouchState";
}
