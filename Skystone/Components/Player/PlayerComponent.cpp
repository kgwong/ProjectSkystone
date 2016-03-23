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

void PlayerComponent::handleEvent(const ComponentEvent& e)
{
	switch (e.getType())
	{
	case ComponentEvent::Type::onDeath:
		e.getScene().setNextScene(SceneID::GAME_OVER);
		break;
	case ComponentEvent::Type::onDamageTaken:
		LOG("GAME") << "Hit by enemy! " << health_->getHealth() << "hp left";
		health_->setInvincible(true);
		//owner_.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::stunState);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(&PlayerMovementState::stunState);

		if (physics_->isMovingLeft())
		{
			physics_->setVelX(10 * 60.0f);
		}
		else
		{
			physics_->setVelX(-10 * 60.0f);
		}
		physics_->setVelY(-10 * 60.0f);
		break;
	default:
		break;
	}
}

void PlayerComponent::handleEvent(const CollisionEvent& e)
{
	switch (e.getOtherObject().getType())
	{
	case GameObject::Type::DROP:
		health_->heal(10);
		LOG("GAME") << "Picked up a thing to heal 10hp!";
		break;
	case GameObject::Type::ENEMY:
		DamageComponent* damage = e.getOtherObject().getComponent<DamageComponent>();
		if (health_->takeDamage(damage->getDamage()))
		{
			owner_.broadcastEvent(ComponentEvent(ComponentEvent::Type::onDamageTaken, e.getScene()));
		}
		break;
	}
}
