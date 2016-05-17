#include "HangState.h"
#include "Components/Player/Attack/PlayerHookState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"
#include "GameMath/CircleMath.h"
#include "LaunchState.h"
#include "Components/Player/Attack/Aim/AimState.h"

//CONSTANTS
const float HangState::MAX_ANGLE = 80.0f;
const float HangState::DEFAULT_SPEED = 4.24f;
const float HangState::MAX_SPEED = 5.24f;
const float HangState::MIN_ROPE_LENGTH = 10.0f;
const float HangState::MAX_ROPE_LENGTH = 75.0f;

HangState::HangState(GameObject& owner)
	:PlayerState(owner)
{
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	ropeLength_ = 0.0f;
	ySpeed_ = 0.0f;
	yDirection_ = 0;
}

HangState::~HangState()
{
}


void HangState::onEnter(Scene& scene)
{
	LOG("HARVEY") << "direction: " << owner_.getComponent<PlayerControlComponent>()->MovementState().direction;
	if (scene.gameObjects.playerHook == nullptr)
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		return;
	}
	if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookDisconnectState")
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		return;
	}
	//CANNOT change physics here....must do in update.
	hookPosition_ = scene.gameObjects.playerHook->getPos();
	ropeLength_ = fabsf(hookPosition_.y - owner_.getPosY());
	hookPosition_ = scene.gameObjects.playerHook->getPos();
	hangPosition_ = owner_.getPos();
	owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(0);
	ySpeed_ = DEFAULT_SPEED;
	yDirection_ = 0;
	
	AimState playerAim = owner_.getComponent<PlayerControlComponent>()->HookState().getAimState();
	
	//possible solution - put getting direction from keyboard input in separate state.
	//write it independent of control code input.
	//glitch is that it always swings.. from swing to hang!!!!

	float xDistance = hookPosition_.x - owner_.getPosX();
	LOG("HARVEY") << "HOOKPOSITION: " << hookPosition_;
	LOG("HARVEY") << "owner position: " << owner_.getPos();
	LOG("HARVEY") << "AIM STATE: " << owner_.getComponent<PlayerControlComponent>()->HookState().AimStateName();

	if (playerAim != AimState::UP)
	{
		if (playerAim == AimState::LEFT)
			owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(-1);
		else if (playerAim == AimState::RIGHT)
			owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(1);

		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "SwingState");
	}
	else
	{
		//player will teleport right under hook
		hangPosition_.x = hookPosition_.x;
		hangPosition_.y = ropeLength_ + hookPosition_.y;
	}
}
void HangState::onExit(Scene& scene)
{
	//reset everything
	hookPosition_.x = 0.0f;
	hookPosition_.y = 0.0f;
	ropeLength_ = 0.0f;
	ySpeed_ = 0.0f;
	yDirection_ = 0;
	hangPosition_.x = 0.0f;
	hangPosition_.y = 0.0f;


}
void HangState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, ControlType::UP))
	{
		ySpeed_ += 0.65f;
		if (ySpeed_ > MAX_SPEED)
			ySpeed_ = MAX_SPEED;
		yDirection_ = -1;
	}
	else if (GameInputs::keyDown(e, ControlType::DOWN))
	{
		ySpeed_ += 0.65f;
		if (ySpeed_ > MAX_SPEED)
			ySpeed_ = MAX_SPEED;
		yDirection_ = 1;
	}
	else if (GameInputs::keyDown(e, ControlType::LEFT) || GameInputs::keyDown(e,ControlType::RIGHT))
	{
		if (GameInputs::keyDown(e, ControlType::LEFT))
			owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(-1);
		else
			owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(1);

		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "SwingState");
		owner_.getComponent<PhysicsComponent>()->enableGravity(false);
	}
	else
		yDirection_ = 0;

}

void HangState::handleEvent(const CollisionEvent & e)
{
}
void HangState::update(Scene& scene)
{
	if (owner_.getComponent<PlayerControlComponent>()->MovementState().direction == 0)
	{
		if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookLaunchState")
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		}
		else if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookDisconnectState")
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
			owner_.getComponent<PhysicsComponent>()->enableGravity(true);
		}
		else
		{
			auto playerPhysics = owner_.getComponent<PhysicsComponent>();
			//if not turned off will build downward velocity
			playerPhysics->enableGravity(false);

			hangPosition_.y += ySpeed_ * yDirection_;
			ropeLength_ = fabsf(hangPosition_.y - hookPosition_.y);

			if (MIN_ROPE_LENGTH > ropeLength_)
			{
				ropeLength_ = MIN_ROPE_LENGTH;
				hangPosition_.y -= ySpeed_ * yDirection_;
			}

			owner_.setPos(hangPosition_);
		}
	}
	
}



