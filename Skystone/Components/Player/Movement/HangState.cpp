#include "HangState.h"
#include "Components/Player/Attack/PlayerHookState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "GameMath/CircleMath.h"


//CONSTANTS
const float HangState::MAX_ANGLE = 80.0f;
const float HangState::DEFAULT_SPEED = 4.5f;
const float HangState::MAX_SPEED = 16.4f;

HangState::HangState()
{
	swingVector_.x = 0.0f;
	swingVector_.y = 0.0f;
	direction_ = 0;
	currentAngle_ = 0.0f;
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	radius_ = 0.0f;
}

HangState::~HangState()
{
}


void HangState::onEnter(GameObject& player)
{
	//CANNOT change physics here....must do in update.
	hookPosition_ = player.getComponent<PlayerControlComponent>()->HookState().getPosition();
	radius_ = fabsf(hookPosition_.y - player.getPosY());
	oldPlayerYVelocity = player.getComponent<PhysicsComponent>()->getVelY();

}
void HangState::onExit(GameObject& player)
{
	//reset everything
	swingVector_.x = 0.0f;
	swingVector_.y = 0.0f;
	direction_ = 0;
	currentAngle_ = 0.0f;
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	radius_ = 0.0f;

}
void HangState::handleInput(GameObject& player, SDL_Event& e)
{
	//controls swinging motion only. 
	//Look in PlayerHookState's connectState to see how hook gets created/destroyed.
	if (GameInputs::keyDown(e, ControlType::LEFT))
	{
		direction_ = -1;
	}
	else if (GameInputs::keyDown(e, ControlType::RIGHT))
	{
		direction_ = 1;
	}
}
void HangState::update(GameObject& player)
{
	if (!player.getComponent<PlayerControlComponent>()->HookState().hanging)
	{
		player.getComponent<PlayerControlComponent>()->changeMovementState(&PlayerMovementState::airborneState);
		player.getComponent<PhysicsComponent>()->enableGravity(true);
	}
	else
	{
		auto playerPhysics = player.getComponent<PhysicsComponent>();
		playerPhysics->enableGravity(false);
		
		playerPhysics->setVelY(0);
		if (currentAngle_ > MAX_ANGLE)
		{
			direction_ = -direction_;
			currentAngle_ = MAX_ANGLE;
		}
		if (currentAngle_ < -MAX_ANGLE)
		{
			direction_ = -direction_;
			currentAngle_ = -MAX_ANGLE;
		}

		if (direction_ > 0)
			currentAngle_ += 3.14f;
		if (direction_ < 0)
			currentAngle_ -= 3.14f;

		swingVector_.x = hookPosition_.x + sin(toRadians(currentAngle_)) * radius_;
		swingVector_.y = hookPosition_.y + cos(toRadians(currentAngle_)) * radius_;
		//LOG("INFO") << swingVector_;
		//LOG("INFO") << "ANGLE: " << currentAngle_;
		//LOG("INFO") << "RADIUS: " << radius_;
		player.setPos(swingVector_);
	}
	
}
