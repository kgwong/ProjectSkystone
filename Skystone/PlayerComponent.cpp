#include "PlayerComponent.h"

#include "GameOverException.h"
#include "HealthComponent.h"
#include "DamageComponent.h"
#include "PhysicsComponent.h"
#include "PlayerMovementState.h"
#include "PlayerControlComponent.h"

#include "Direction.h"

PlayerComponent::PlayerComponent(GameObject& owner)
	:NonUpdatingComponent(owner)
{
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::start(Level & level)
{
	health_ = owner_.getComponent<HealthComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void PlayerComponent::handleEvent(const ComponentEvent& e)
{
	switch (e.getType())
	{
	case ComponentEvent::Type::onDeath:
		throw GameOverException();
		break;
	case ComponentEvent::Type::onDamageTaken:
		std::cout << "Hit by enemy! " << health_->getHealth() << "hp left" << std::endl;
		health_->setInvincible(true);
		//owner_.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::stunState);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(&PlayerMovementState::stunState);

		if (physics_->isMovingLeft())
		{
			physics_->setVelX(10);
		}
		else
		{
			physics_->setVelX(-10);
		}
		physics_->setVelY(-10);
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
		std::cout << "Picked up a thing to heal 10hp!" << std::endl;
		break;
	case GameObject::Type::ENEMY:
		DamageComponent* damage = e.getOtherObject().getComponent<DamageComponent>();
		if (health_->takeDamage(damage->getDamage()))
		{
			owner_.broadcastEvent(ComponentEvent(ComponentEvent::Type::onDamageTaken, e.getLevel()));
		}
		break;
	}
}
