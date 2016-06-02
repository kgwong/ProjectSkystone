#include "SwingState.h"
#include "Application/Log.h"
#include "GameMath/CircleMath.h"
#include "Game/GameTime.h"

const float SwingState::ANGLE_RANGE = 80.0f;
const float SwingState::RESTING_ANGLE = 90.0f;
const float SwingState::STARTING_SPEED = 2.24f;
const float SwingState::MAX_SPEED = 10.24f;

SwingState::SwingState(GameObject & owner) : PlayerState(owner) {}
SwingState::~SwingState() {}

void SwingState::onEnter(Scene & scene)
{
	if (verifiedState(scene))
	{
		physics_ = owner_.getComponent<PhysicsComponent>();
		stateManager_ = owner_.getComponent<PlayerControlComponent>();
		xSpeed_ = STARTING_SPEED;
		//obtain variables from previous state.
		angle_ = stateManager_->MovementState().angle;
		orient_ = stateManager_->MovementState().direction;
		if (orient_ > 0)
			xDirection_ = -1;
		else
			xDirection_ = 1;

		radius_ = stateManager_->MovementState().radius;
		swingPosition_ = owner_.getPos();
		oldPosition_ = owner_.getPos();
		hookPosition_ = scene.gameObjects.playerHook->getPos();

		LOG("HARVEY") << "ON ENTER angle in degrees: " << angle_;
		LOG("HARVEY") << "ON ENTER angle in radians: " << toRadians(angle_);
		LOG("HARVEY") << "ON ENTER radius: " << radius_;
		LOG("HARVEY") << "ON ENTER hook Position: " << hookPosition_;
		LOG("HARVEY") << "ON ENTER player position: " << swingPosition_;
		LOG("HARVEY") << "ON ENTER direction: " << xDirection_;
	}
	else
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
	}

}

void SwingState::onExit(Scene & scene)
{
	stateManager_->MovementState().setDirection(xDirection_);
	stateManager_->MovementState().setSpeed(xSpeed_);
	stateManager_->MovementState().setAngle(angle_);
	stateManager_->MovementState().setRadius(radius_);
	if (angleRange_ <= 0)
	{
		stateManager_->MovementState().setAngle(RESTING_ANGLE);
	}
	resetVariables();
}

void SwingState::handleInput(Scene & scene, SDL_Event & e)
{
	if (GameInputs::keyDown(e, ControlType::LEFT))
	{
		keyHeld_ = true;
		xDirection_ = -1;
		orient_ = 1;
		xSpeed_ += 0.8f;
		if (xSpeed_ > MAX_SPEED)
		{
			xSpeed_ = MAX_SPEED;
		}

		angleRange_++;
		if (angleRange_ >= ANGLE_RANGE)
			angleRange_ = ANGLE_RANGE;

	}
	else if (GameInputs::keyDown(e, ControlType::RIGHT))
	{
		keyHeld_ = true;
		xDirection_ = 1;
		orient_ = -1;
		xSpeed_ += 0.06f;
		if (xSpeed_ > MAX_SPEED)
		{
			xSpeed_ = MAX_SPEED;
		}

		angleRange_++;
		if (angleRange_ >= ANGLE_RANGE)
			angleRange_ = ANGLE_RANGE;
	}

	if (GameInputs::keyDown(e, ControlType::LAUNCH_HOOK))
	{
		stateManager_->MovementState().setDirection(xDirection_);
		stateManager_->MovementState().setXVelocity(xVelocity);
		stateManager_->changeMovementState(scene, "Launch");
	}
}

void SwingState::update(Scene & scene)
{
	if (enemyHit_)
	{
		stateManager_->changeMovementState(scene, "AirborneState");
		return;
	}

    LOG("HARVEY") << "UPDATE angle in degrees: " << angle_;
	physics_->enableGravity(false);

	if (angle_ > angleRange_ * 2 + 10)
	{
		angle_ = angleRange_ * 2 + 10;
		xDirection_ = -xDirection_;
	}

	if (angle_ < RESTING_ANGLE - angleRange_)
	{
		angle_ = RESTING_ANGLE - angleRange_;
		xDirection_ = -xDirection_;
	}
	
	//reduce angle over time.
	angleRange_ -= 0.06f;
	xSpeed_ -= (xSpeed_ * .15f);
	if (xSpeed_ < STARTING_SPEED)
		xSpeed_ = STARTING_SPEED;
	if (angleRange_ <= 0)
	{
		stateManager_->changeMovementState(scene, "Hang");
		return;
	}

	angle_ += xSpeed_ * xDirection_;

	float dx = swingPosition_.x - hookPosition_.x;
	float dy = swingPosition_.y - hookPosition_.y;
	radius_ = sqrtf((dx * dx) + (dy * dy));

	swingPosition_.x = hookPosition_.x + cos(angle_ * M_PI / 180.0f) * radius_;
	swingPosition_.y = hookPosition_.y + sin(angle_ * M_PI / 180.0f) * radius_;
	

	float deltax = swingPosition_.x - oldPosition_.x;
	float deltay = swingPosition_.y - oldPosition_.y;
	xVelocity = deltax / Time::getElapsedUpdateTimeSeconds();
	yVelocity = deltay / Time::getElapsedUpdateTimeSeconds();
	physics_->setVelX(xVelocity);
	physics_->setVelY(yVelocity);

	oldPosition_ = swingPosition_;
}

std::string SwingState::name(){ return "SwingState"; }

void SwingState::resetVariables()
{
	xSpeed_ = 0.0f;
	angle_ = 0.0f;
	xDirection_ = 0.0f;
	swingPosition_ = Point { 0.0f, 0.0f };
	hookPosition_ = Point{ 0.0f, 0.0f };
	oldPosition_ = Point{ 0.0f, 0.0f };
	radius_ = 0.0f;
	swingTime_ = 0.0f;
	damp_ = 0.0f;
	keyHeld_ = false;
	timer_ = 0.0f;
	angleRange_ = ANGLE_RANGE;
	physics_->enableGravity(true);
	enemyHit_ = false;
}

bool SwingState::verifiedState(Scene & scene)
{
	if (scene.gameObjects.playerHook == nullptr || owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() != "HookConnectState")
	{
		return false;
	}

	return true;
}

void SwingState::handleEvent(const CollisionEvent & e)
{
	if (e.getOtherObject().getType() == GameObject::Type::ENEMY)
	{
		enemyHit_ = true;
	}
}
