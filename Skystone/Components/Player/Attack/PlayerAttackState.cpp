#include "PlayerAttackState.h"

#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/Movement/PlayerState.h"

#include "Game/GameInputs.h"

#include "Application/Log.h"

#include "Resources/Resources.h"

#include "GameMath/CircleMath.h"


PlayerAttackState::PlayerAttackState(GameObject& owner)
	:InputComponent(owner),
	defaultAimState(owner),
	aimUpState(owner),
	currentState_(&defaultAimState),
	aimState_(AimState::RIGHT),
	degrees_(0),
	shoot_(false)
	//launch_(false)
{
}


PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::handleInput(Scene& scene, SDL_Event& e)
{
	currentState_->handleInput(scene, e);
	if (GameInputs::keyDown(e, ATTACK))
	{
		shoot_ = true;
	}
}

void PlayerAttackState::start(Scene& scene)
{
	defaultAimState.start(scene);
	aimUpState.start(scene);
}

void PlayerAttackState::update(Scene& scene)
{
	
	currentState_->update(scene);
	degrees_ = currentState_->getAngle();
	if (shoot_)
	{
		//level.addPlayerProjectileAtLocation(owner_.getPos(), PROJECTILE_VELOCITY, degrees_);
		auto bullet = scene.gameObjects.add("PlayerProjectile", "", owner_.getPos());
		auto physics = bullet->getComponent<PhysicsComponent>();
		float newVelX = (float)PROJECTILE_VELOCITY * cos(toRadians(degrees_));
		float newVelY = (float)PROJECTILE_VELOCITY * sin(toRadians(degrees_));
		physics->setVelX(newVelX * 60.0f);
		physics->setVelY(newVelY * 60.0f);
		shoot_ = false;

		Resources::audioPlayer.PlayClip("laser1");
	}


	/*if (launch_)
	{
		int testVelocity = 5;
		level.addPlayerHookAtLocation(owner_.getPos(), testVelocity, degrees_);
		launch_ = false;
	}*/
}

void PlayerAttackState::changeState(Scene& scene, const std::string& stateName)
{
	currentState_->onExit(scene);
	currentState_ = getStateFromName(stateName);
	currentState_->onEnter(scene);
}

PlayerAimState* PlayerAttackState::getStateFromName(const std::string& name)
{
	if (name == defaultAimState.name())
	{
		return &defaultAimState;
	}
	else if (name == aimUpState.name())
	{
		return &aimUpState;
	}
	else
	{
		LOG("ERROR") << "Unknown state";
		return nullptr;
	}
}
