#include "HangState.h"

#include"Application/Log.h"

const float HangState::RESTING_ANGLE = 90.0f;
const float HangState::MAX_SPEED = 56.24f;
const float HangState::STARTING_SPEED = 24.36f;

HangState::HangState(GameObject& owner) : PlayerState(owner) {}
HangState::~HangState() {}

void HangState::onEnter(Scene& scene)
{	
	if (verifiedState(scene))
	{
		physics_ = owner_.getComponent<PhysicsComponent>();
		stateManager_ = owner_.getComponent<PlayerControlComponent>();
		playerPos_ = owner_.getPos();
		hookPosition_ = scene.gameObjects.playerHook->getPos();
		yDirection_ = 0;
		ySpeed_ = STARTING_SPEED;

		float dx = playerPos_.x - hookPosition_.x;
		float dy = playerPos_.y - hookPosition_.y;
		angle_ = atan2f(dy, dx) * (180 / M_PI);

		if (angle_ < 0)
		{
			stateManager_->changeMovementState(scene, "AirborneState");
		}
		else if (angle_ != RESTING_ANGLE)
		{
			radius_ = sqrtf((dx * dx) + (dy * dy));
			stateManager_->MovementState().setDirection(swingDirection());
			stateManager_->MovementState().setAngle(angle_);
			stateManager_->MovementState().setRadius(radius_);
			stateManager_->changeMovementState(scene, "SwingState");
		}
		else
		{
			radius_ = dy;
		}

		LOG("HARVEY") << "STARTING ANGLE: " << angle_;
	}
	else
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
	}


}

void HangState::onExit(Scene& scene)
{
	resetVariables();
}

void HangState::handleInput(Scene& scene,SDL_Event& e)
{
	if (GameInputs::keyDown(e, ControlType::UP))
	{
		yDirection_ = -1;
		increaseSpeed();
	}	
	else if (GameInputs::keyDown(e, ControlType::DOWN))
	{
		yDirection_ = 1;
		increaseSpeed();
	}
	else if (GameInputs::keyDown(e, ControlType::LEFT))
	{
		stateManager_->MovementState().setDirection(-1);
		stateManager_->MovementState().setDirection(swingDirection());
		stateManager_->MovementState().setAngle(angle_);
		stateManager_->MovementState().setRadius(radius_);
		stateManager_->changeMovementState(scene, "SwingState");
	}
	else if (GameInputs::keyDown(e, ControlType::RIGHT))
	{
		stateManager_->MovementState().setDirection(1);
		stateManager_->MovementState().setDirection(swingDirection());
		stateManager_->MovementState().setAngle(angle_);
		stateManager_->MovementState().setRadius(radius_);
		stateManager_->changeMovementState(scene, "SwingState");
	}
	else
	{
		yDirection_ = 0;
		ySpeed_ = STARTING_SPEED;
	}
}

void HangState::handleEvent(const CollisionEvent & e)
{
}

void HangState::update(Scene & scene)
{
	if (verifiedState(scene))
	{
		//update velocity of hook here.
		physics_->enableGravity(false);
		physics_->setVelY(0.0f);
	
		//projected playerPosition
		Point projectedPosition = playerPos_;
		projectedPosition.y += ySpeed_ * yDirection_;
		float dy = projectedPosition.y - hookPosition_.y;
		float hookHeight = scene.gameObjects.playerHook->getComponent<ColliderComponent>()->getHeight();		
		
		if (dy >= hookHeight)
		{
			physics_->setVelY(ySpeed_ * yDirection_ * Time::getElapsedUpdateTime());
			playerPos_ = owner_.getPos();
			radius_ = playerPos_.y - hookPosition_.y;
		/*	LOG("HARVEY") << "radius: " << radius_;
			LOG("HARVEY") << "hook height: " << hookHeight;*/
		}

	}
	else
	{
		stateManager_->changeMovementState(scene, "AirborneState");
	}
}

void HangState::resetVariables()
{
	angle_ = RESTING_ANGLE;
	playerPos_ = Point{ 0.0f, 0.0f };
	hookPosition_ = Point{ 0.0f, 0.0f };
	radius_ = 0.0f;
	yDirection_ = 0;
	physics_->enableGravity(true);
}

std::string HangState::name() { return "Hang"; }

bool HangState::verifiedState(Scene& scene)
{
	if (scene.gameObjects.playerHook == nullptr || owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() != "HookConnectState")
	{
		return false;
	}

	return true;
}

void HangState::increaseSpeed()
{
	ySpeed_ += 0.4f;
	if (ySpeed_ > MAX_SPEED)
		ySpeed_ = MAX_SPEED;
}

int HangState::swingDirection()
{
	int playerDirection = 0;
	float xdist = Point::getXDirection(playerPos_, hookPosition_);
	if (xdist != 0 && stateManager_->MovementState().getPrevState()->name() != "SwingState")
		playerDirection = (fabsf(xdist) / (int)xdist);
	
	if (playerDirection > 0)
		return -1;
	if (playerDirection < 0)
		return 1;
	
	return 0;
}

