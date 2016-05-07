#include "CrouchState.h"

#include "../PlayerControlComponent.h"

#include "Components/Render/SpriteRenderer.h"
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
	renderer_->setSprite("Images/crouch cycle.png");
	ColliderComponent::BoxCollider newBoxCollider = {0, 0, 48, 32};
	collider_->setCollider(newBoxCollider);
	collider_->setOffsetY(32);

	physics_->setVelX(0);
}

void CrouchState::onExit(Scene& scene)
{
	ColliderComponent::BoxCollider newBoxCollider = { 0, 0, 48, 64 };
	collider_->setCollider(newBoxCollider);
	collider_->setOffsetY(0);
}

void CrouchState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, DOWN))
	{
		controlComponent_->changeMovementState(scene, "WalkingState");
	}

	if (GameInputs::keyDown(e, LEFT))
	{
		renderer_->setFlipHorz(true);
	}
	if (GameInputs::keyDown(e, RIGHT))
	{
		renderer_->setFlipHorz(false);
	}
}

void CrouchState::update(Scene& scene)
{
}

void CrouchState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	renderer_ = owner_.getComponent<SpriteRenderer>();
	collider_ = owner_.getComponent<ColliderComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
}

std::string CrouchState::name()
{
	return "CrouchState";
}
