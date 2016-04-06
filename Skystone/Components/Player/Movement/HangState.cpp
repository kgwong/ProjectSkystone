#include "HangState.h"
#include "Components/Player/Attack/PlayerHookState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "GameMath/CircleMath.h"
#include "LaunchState.h"


//CONSTANTS
const float HangState::MAX_ANGLE = 80.0f;
const float HangState::DEFAULT_SPEED = 3.14f;
const float HangState::MAX_SPEED = 8.45f;

HangState::HangState()
{
	swingVector_.x = 0.0f;
	swingVector_.y = 0.0f;
	direction_ = 0;
	currentAngle_ = 0.0f;
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	radius_ = 0.0f;
	currentSpeed_ = DEFAULT_SPEED;
	direction_ = 1;
}

HangState::~HangState()
{
}


void HangState::onEnter(Scene& scene, GameObject& player)
{
	//CANNOT change physics here....must do in update.
	hookPosition_ = player.getComponent<PlayerControlComponent>()->HookState().getPosition();
	radius_ = fabsf(hookPosition_.y - player.getPosY());
	oldPlayerYVelocity = player.getComponent<PhysicsComponent>()->getVelY();
	oldPlayerPos_ = player.getPos();
	player.getComponent<PlayerControlComponent>()->MovementState().setCanSwing(true);
	direction_ = 1;
}
void HangState::onExit(Scene& scene, GameObject& player)
{

	//player.getComponent<PlayerControlComponent>()->MovementState().setDirection(direction_);
	//LOG("INFO") << "this direction: " << direction_;
	//LOG("INFO") << "component direction: " << player.getComponent<PlayerControlComponent>()->MovementState().direction;
	//reset everything
	swingVector_.x = 0.0f;
	swingVector_.y = 0.0f;
	//direction_ = 1;
	currentAngle_ = 0.0f;
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	radius_ = 0.0f;
	currentSpeed_ = DEFAULT_SPEED;


}
void HangState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{
	//controls swinging motion only. 
	//Look in PlayerHookState's connectState to see how hook gets created/destroyed.
	if (GameInputs::keyDown(e, ControlType::LEFT))
	{
		if (direction_ > 0)
		{
			currentSpeed_ -= 0.2f;
			if (currentSpeed_ <= DEFAULT_SPEED)
				currentSpeed_ = DEFAULT_SPEED;
		}
		else
		{
			currentSpeed_ += 0.2f;
			if (currentSpeed_ > MAX_SPEED)
				currentSpeed_ = MAX_SPEED;
		}
		//direction_ = -1;
	}
	else if (GameInputs::keyDown(e, ControlType::RIGHT))
	{

		if (direction_ < 0)
		{
			currentSpeed_-= 0.2f;
			if (currentSpeed_ <= DEFAULT_SPEED)
				currentSpeed_ = DEFAULT_SPEED;
		}
		else
		{
			currentSpeed_ += 0.2f;
			if (currentSpeed_ > MAX_SPEED)
				currentSpeed_ = MAX_SPEED;
		}
		//direction_ = 1;
	}
}
void HangState::update(Scene& scene, GameObject& player)
{
	if (player.getComponent<PlayerControlComponent>()->HookState().getState() == &PlayerHookState::launchState)
	{
		player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::airborneState);
		player.getComponent<PlayerControlComponent>()->HookState().setHanging(false);
		player.getComponent<PhysicsComponent>()->enableGravity(true);
		return;
	}

	if (!player.getComponent<PlayerControlComponent>()->HookState().hanging)
	{
		player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::launchState);
		player.getComponent<PhysicsComponent>()->enableGravity(true);
	}
	else
	{
	//	LOG("INFO") << "Direction: " << direction_;
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
			currentAngle_ += currentSpeed_;
		if (direction_ < 0)
			currentAngle_ -= currentSpeed_;

		swingVector_.x = hookPosition_.x + sin(toRadians(currentAngle_)) * radius_;
		swingVector_.y = hookPosition_.y + cos(toRadians(currentAngle_)) * radius_;
		
		//player.getComponent<PhysicsComponent>()->setVelX(swingVector_.x);
		//player.getComponent<PhysicsComponent>()->setVelY(swingVector_.y);
		if (player.getComponent<PlayerControlComponent>()->MovementState().canSwing)
		{
			oldPlayerPos_ = swingVector_;
			player.setPos(swingVector_);
		}
		else if (player.getComponent<PlayerControlComponent>()->MovementState().getState() == &PlayerMovementState::hangState)
		{
			player.getComponent<PlayerControlComponent>()->MovementState().setCanSwing(true);
		}
	}
	
}

Point HangState::SwingVector()
{
	return swingVector_;
}

Point HangState::OldPlayerPos()
{
	return oldPlayerPos_;
}

int HangState::getDirection()
{
	return direction_;
}
