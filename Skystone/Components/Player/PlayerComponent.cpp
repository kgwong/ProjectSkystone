#include "PlayerComponent.h"

#include "Components/Common/HealthComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Movement/PlayerMovementState.h"
#include "PlayerControlComponent.h"

#include "GameTypes/Direction.h"

#include "Application/Log.h"

PlayerComponent::PlayerComponent(GameObject& owner)
	:NonUpdatingComponent(owner)
{
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::start(Scene& scene)
{
	health_ = owner_.getComponent<HealthComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void PlayerComponent::handleEvent(const CollisionEvent& e)
{
	DamageComponent* pDamage = e.getOtherObject().getComponent<DamageComponent>();

	switch (e.getOtherObject().getType())
	{
	case GameObject::Type::DROP:
		health_->heal(10);
		LOG("GAME") << "Picked up a thing to heal 10hp!";
		break;
	case GameObject::Type::ENEMY_PROJECTILE:
		health_->takeDamage(pDamage->getDamage());
		break;
	case GameObject::Type::ENEMY:
		DamageComponent* damage = e.getOtherObject().getComponent<DamageComponent>();
		if (health_->takeDamage(damage->getDamage()))
		{
			owner_.broadcastEvent(DamageTakenEvent(e.getScene()));
		}
		break;
	}
}

void PlayerComponent::handleEvent(const OnDeathEvent& e)
{
	e.getScene().setNextScene(SceneID::GAME_OVER);
}

void PlayerComponent::handleEvent(const DamageTakenEvent& e)
{
	LOG("GAME") << "Hit by enemy! " << health_->getHealth() << "hp left";
	health_->setInvincible(true);
	owner_.getComponent<PlayerControlComponent>()->changeMovementState(e.getScene(), "StunState");

	if (physics_->isMovingLeft())
	{
		physics_->setVelX(10 * 60.0f);
	}
	else
	{
		physics_->setVelX(-10 * 60.0f);
	}
	physics_->setVelY(-10 * 60.0f);
}
