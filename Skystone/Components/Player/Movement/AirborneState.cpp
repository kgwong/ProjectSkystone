#include "AirborneState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"
#include "Application/Log.h"
#include "Components/Render/SpriteAnimator.h"

AirborneState::AirborneState(GameObject& owner)
	:PlayerState(owner),
	controlComponent_(nullptr),
	physics_(nullptr),
	animator_(nullptr)
{
}


AirborneState::~AirborneState()
{
}

//Airborne state can mean that you are either falling or jumping which is not explicitly expressed as 2 different PlayerStates.
void AirborneState::onEnter(Scene& scene)
{

	//useful if switching between levels because airbornestate is a vague state to be in.
	if (physics_->isFalling())
	{
		//LOG("HARVEY") << "I am FALLING";
		physics_->enableGravity(true);
	}
	animator_->setSpriteSheet("Images/jump cycle.png");
}

void AirborneState::onExit(Scene& scene)
{

}

void AirborneState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyHeld(JUMP))
	{
		if (GameInputs::keyDown(e, JUMP))
		{
			controlComponent_->changeMovementState(scene, "FlyingState");
		}
	}
}

void AirborneState::handleEvent(const CollisionEvent & e)
{
	if (e.getOtherObject().getType() == GameObject::Type::TILE)
	{
	}
}

void AirborneState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
	animator_ = owner_.getComponent<SpriteAnimator>();
}

void AirborneState::update(Scene& scene)
{
	if (controlComponent_->HookState().getState()->name() == "HookConnectState")
	{
		controlComponent_->changeMovementState(scene, "Hang");
		return;
	}

	if (!physics_->isFalling())
	{
		controlComponent_->changeMovementState(scene, "WalkingState");
		return;
	}

	if (GameInputs::keyHeld(LEFT))
	{
		physics_->setVelX(-5 * 60.0f);
		animator_->setFlipHorz(true);
	}
	else if (GameInputs::keyHeld(RIGHT))
	{
		physics_->setVelX(5 * 60.0f);
		animator_->setFlipHorz(false);
	}
	else
	{
		physics_->setVelX(0);
	}
}

std::string AirborneState::name()
{
	return "AirborneState";
}
