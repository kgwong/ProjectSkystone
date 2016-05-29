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
	aimDiagonalState(owner),
	currentState_(&defaultAimState),
	degrees_(0),
	shoot_(false)
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
	aimDiagonalState.start(scene);
	//call on enter here?
}

void PlayerAttackState::update(Scene& scene)
{
	currentState_->update(scene);
	degrees_ = currentState_->getAngle();
	if (shoot_)
	{
		auto bullet = scene.gameObjects.add("PlayerProjectile", "", getProjectileSpawnPoint());
		auto physics = bullet->getComponent<PhysicsComponent>();
		float newVelX = (float)PROJECTILE_VELOCITY * cos(toRadians(degrees_));
		float newVelY = (float)PROJECTILE_VELOCITY * sin(toRadians(degrees_));
		physics->setVelX(newVelX * 60.0f);
		physics->setVelY(newVelY * 60.0f);
		shoot_ = false;

		Resources::audioPlayer.PlayClip("gunShot");
	}
}

PlayerAimState* PlayerAttackState::getCurrentState()
{
	return currentState_;
}

void PlayerAttackState::changeState(Scene& scene, const std::string& stateName)
{
	currentState_->onExit(scene);
	currentState_ = getStateFromName(stateName);
	currentState_->onEnter(scene);
}

void PlayerAttackState::setShootOffset(Point offset)
{
	shootOffset_ = offset;
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
	else if (name == aimDiagonalState.name())
	{
		return &aimDiagonalState;
	}
	else
	{
		LOG("ERROR") << "Unknown state";
		return nullptr;
	}
}

Point PlayerAttackState::getProjectileSpawnPoint()
{
	return owner_.getPos() + shootOffset_;
}
