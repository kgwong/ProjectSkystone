#include "SwingState.h"
#include "GameMath/CircleMath.h"
#include "Components/Player/PlayerControlComponent.h"
#include "ComponentEvents/CollisionEvent.h"
#include "Components/collider/ColliderComponent.h"
#include "Application/Log.h"
#include "Game/GameConstants.h"

const float SwingState::MAX_ANGLE = 80.0f;

SwingState::SwingState(GameObject& owner)
	:PlayerState(owner)
{
	xSpeed_ = 0.0f;
	currentAngle_ = 0.0f;
	angleRange_ = 0.0f;
	xDirection_ = 0;
	tileHit_ = false;
	tileLeft_  = false;
	tileRight_ = false;
	keyHeld_ = false;
	timer_ = 0.0f;
}

SwingState::~SwingState()
{
}

void SwingState::onEnter(Scene& scene)
{
	xSpeed_ = 1.1f;
	currentAngle_ = 0.0f;
	xDirection_ = owner_.getComponent<PlayerControlComponent>()->MovementState().direction;
	LOG("HARVEY") << "direction is " << xDirection_;
	hookPosition_ = scene.gameObjects.playerHook->getPos();
	swingPosition_ = owner_.getPos();
	oldPosition_ = owner_.getPos();
	radius_ = fabsf(hookPosition_.y - swingPosition_.y);
	tileHit_ = false;
	tileLeft_ = false;
	tileRight_ = false;
	keyHeld_ = false;
	timer_ = 0.0f;
	
	auto physics = owner_.getComponent<PhysicsComponent>();
	swingTime_ = 2 * float(PI) * sqrtf(radius_ / physics->GRAVITY);
	damp_ = 0.075;
	angleRange_ = MAX_ANGLE;//20 should be MIN_ANGLE;

	//this allows player to swing across if hook is shot from the left or right
	AimState playerAim = owner_.getComponent<PlayerControlComponent>()->HookState().disconnectState.getAimState();
	if (playerAim == AimState::RIGHT || playerAim == AimState::LEFT)
	{
		xSpeed_ = 3.141f;
		currentAngle_ = tanhf((swingPosition_.y - hookPosition_.y) / (swingPosition_.x - hookPosition_.x));
		currentAngle_ = toDegrees(currentAngle_);
		float dx = swingPosition_.x - hookPosition_.x;
		float dy = swingPosition_.y - hookPosition_.y;
		radius_ = sqrtf((dx * dx) + (dy * dy));
		angleRange_ = 35;
	}
	LOG("HARVEY") << owner_.getPos();
	LOG("HARVEY") << currentAngle_;
	//LOG("HARVEY") << hookPosition_ << ", " << swingPosition_;
}
void SwingState::onExit(Scene& scene)
{
	owner_.getComponent<PlayerControlComponent>()->MovementState().setSpeed(xSpeed_);
	owner_.getComponent<PlayerControlComponent>()->MovementState().setAngle(currentAngle_);
	owner_.getComponent<PlayerControlComponent>()->MovementState().setRadius(radius_);
	xSpeed_ = 1.1f;
	currentAngle_ = 0.0f;
	xDirection_ = 0;
	radius_ = 0.0f;
	tileHit_ = false;
	tileLeft_ = false;
	tileRight_ = false;
	keyHeld_ = false;
	timer_ = 0.0f;
	angleRange_ = MAX_ANGLE;

}
void SwingState::handleInput(Scene& scene, SDL_Event& e)
{

	if (GameInputs::keyHeld(ControlType::LEFT) || GameInputs::keyHeld(ControlType::RIGHT))
	{
		keyHeld_ = true;
	}

	if (GameInputs::keyUp(e, ControlType::LEFT) || GameInputs::keyUp(e,ControlType::RIGHT))
	{
		keyHeld_ = false;
	}

	if (GameInputs::keyDown(e, ControlType::LAUNCH_HOOK))
	{
		LOG("HARVEY") << "SETTING DIRECTION HERE";
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "Launch");
		owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(xDirection_);
	}
}
void SwingState::update(Scene& scene)
{
	auto playerPhysics = owner_.getComponent<PhysicsComponent>();
	playerPhysics->enableGravity(false);

	if (currentAngle_ > angleRange_)
	{
		currentAngle_ = angleRange_;
		xDirection_ = -xDirection_;
	}
	if (currentAngle_ < -angleRange_)
	{
		currentAngle_ = -angleRange_;
		xDirection_ = -xDirection_;
	}	

	if (keyHeld_)
	{
		timer_ += 0.5f;
		if (timer_ >= swingTime_)
		{
			timer_ = 0.0f;
			angleRange_ += angleRange_ * 1.04f;
			if (angleRange_ > MAX_ANGLE)
				angleRange_ = MAX_ANGLE;
			xSpeed_ *= 1.9f;
			if (xSpeed_ > 6.61f)
				xSpeed_ = 6.61f;
		}

	

	}
	else//damp
	{

		timer_ += 0.5f;
		if (timer_ >= swingTime_)
		{
			timer_ = 0.0f;
			angleRange_ -= angleRange_ * 0.15f;

			xSpeed_ -= (xSpeed_ * .15f);
			if (xSpeed_ < 0.0f)
				xSpeed_ = 0.0f;
		}

		if (angleRange_ < 5)
		{
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "Hang");
			owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(0);
			owner_.setPos(hookPosition_.x, hookPosition_.y + radius_);//where player should be, perfectly aligned with the hook's x-coordinate.
			owner_.getComponent<PlayerControlComponent>()->HookState().setAimState(AimState::UP);
			LOG("HARVEY") << "HI " <<owner_.getComponent<PlayerControlComponent>()->HookState().AimStateName();
			return;
		}
	}

	currentAngle_ += xSpeed_ * xDirection_;

	swingPosition_.x = hookPosition_.x + sin(toRadians(currentAngle_)) * radius_;
	swingPosition_.y = hookPosition_.y + cos(toRadians(currentAngle_)) * radius_;

	if (owner_.getComponent<PlayerControlComponent>()->MovementState().canSwing)
	{
		owner_.setPos(swingPosition_);
		oldPosition_ = swingPosition_;
	}
	else if (!tileHit_)
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "Launch");
	else
	{
		if(tileRight_)
			owner_.setPos(oldPosition_);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		playerPhysics->enableGravity(true);
	}

}

std::string SwingState::name()
{
	return "SwingState";
}

Point SwingState::swingPosition()
{
	return swingPosition_;
}

void SwingState::handleEvent(const CollisionEvent& e)
{
	if (e.getOtherObject().getType() == GameObject::Type::TILE)
	{
		tileHit_ = true;
		auto playerCollider = owner_.getComponent<ColliderComponent>();
		auto tileCollider = e.getOtherObject().getComponent<ColliderComponent>();
		Point offSet;


		//a tile left of player.
		if (owner_.getPosX() + Constants::TILE_SIZE > e.getOtherObject().getPosX())
		{
			tileRight_ = true;
		}
		if (!tileLeft_ && owner_.getPosX() < e.getOtherObject().getPosX() + Constants::TILE_SIZE)
		{
			tileLeft_ = true;
			offSet.x = oldPosition_.x + (Constants::TILE_SIZE / 2);
			offSet.y = oldPosition_.y;
			owner_.setPos(offSet);
		}

		if (tileLeft_)
		{
			tileRight_ = false;		
		}
		//owner_.setPos(offSet);
	}
}
