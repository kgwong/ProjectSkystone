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
	xDirection_ = 0;
	tileHit_ = false;
	tileLeft_  = false;
	tileRight_ = false;
}

SwingState::~SwingState()
{
}

void SwingState::onEnter(Scene& scene)
{
	xSpeed_ = 0.0f;
	currentAngle_ = 0.0f;
	xDirection_ = owner_.getComponent<PlayerControlComponent>()->MovementState().direction;

	hookPosition_ = scene.gameObjects.playerHook->getPos();
	swingPosition_ = owner_.getPos();
	oldPosition_ = owner_.getPos();
	radius_ = fabsf(hookPosition_.y - swingPosition_.y);
	tileHit_ = false;
	tileLeft_ = false;
	tileRight_ = false;

	
	//LOG("HARVEY") << hookPosition_ << ", " << swingPosition_;
}
void SwingState::onExit(Scene& scene)
{
	owner_.getComponent<PlayerControlComponent>()->MovementState().setDirection(xDirection_);
	xSpeed_ = 0.0f;
	currentAngle_ = 0.0f;
	xDirection_ = 0;
	tileHit_ = false;
	tileLeft_ = false;
	tileRight_ = false;

}
void SwingState::handleInput(Scene& scene, SDL_Event& e)
{

	if (GameInputs::keyHeld(ControlType::LEFT) ||
		GameInputs::keyHeld(ControlType::RIGHT))
	{
		xSpeed_ += 0.75f;
		if (xSpeed_ > 3.141f)
			xSpeed_ = 3.141f;
	}
	else
	{
		
		xSpeed_ -= 0.25f;
		if (xSpeed_ <= 0.0f)
		{
			xSpeed_ = 0.0f;
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "Hang");
		}
	}

	if (GameInputs::keyDown(e, ControlType::LAUNCH_HOOK))
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "Launch");
	}
}
void SwingState::update(Scene& scene)
{
	auto playerPhysics = owner_.getComponent<PhysicsComponent>();
	playerPhysics->enableGravity(false);

	if (currentAngle_ > MAX_ANGLE)
	{
		currentAngle_ = MAX_ANGLE;
		xDirection_ = -xDirection_;
	}
	if (currentAngle_ < -MAX_ANGLE)
	{
		currentAngle_ = -MAX_ANGLE;
		xDirection_ = -xDirection_;
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
