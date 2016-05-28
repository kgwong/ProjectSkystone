#include "CrouchState.h"

#include "../PlayerControlComponent.h"

#include "Components/Render/SpriteAnimator.h"
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
	animator_->setSpriteSheet("Images/crouch cycle.png");
	animator_->setTimesToPlay(1);
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

	if (GameInputs::keyDown(e, LEFT))
	{
		animator_->setFlipHorz(true);
	}
	if (GameInputs::keyDown(e, RIGHT))
	{
		animator_->setFlipHorz(false);
	}
}

void CrouchState::update(Scene& scene)
{
}

void CrouchState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	animator_ = owner_.getComponent<SpriteAnimator>();
	collider_ = owner_.getComponent<ColliderComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
}

std::string CrouchState::name()
{
	return "CrouchState";
}
