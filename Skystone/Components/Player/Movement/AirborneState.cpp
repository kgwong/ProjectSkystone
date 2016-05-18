#include "AirborneState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"
#include "Application/Log.h"

AirborneState::AirborneState(GameObject& owner)
	:PlayerState(owner)
{
}


AirborneState::~AirborneState()
{
}

//Airborne state can mean that you are either falling or jumping which is not explicitly expressed as 2 different PlayerStates.
void AirborneState::onEnter(Scene& scene)
{
	renderer_->setSprite("Images/jump cycle.png");

	//useful if switching between levels because airbornestate is a vague state to be in.
	if (physics_->isFalling())
	{
		//LOG("HARVEY") << "I am FALLING";
		physics_->enableGravity(true);
	}
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
	renderer_ = owner_.getComponent<SpriteRenderer>();
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
		renderer_->setFlipHorz(true);
	}
	else if (GameInputs::keyHeld(RIGHT))
	{
		physics_->setVelX(5 * 60.0f);
		renderer_->setFlipHorz(false);
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
