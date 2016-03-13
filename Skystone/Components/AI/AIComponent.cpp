#include "AIComponent.h"

#include "Components/Common/HealthComponent.h"
#include "Components/Common/DamageComponent.h"

AIComponent::AIComponent(GameObject & owner)
	:Component(owner)
{

}

AIComponent::~AIComponent()
{
}

void AIComponent::handleEvent(const CollisionEvent& e)
{
	GameObject& other = e.getOtherObject();
	if (other.getType() == GameObject::Type::PLAYER_PROJECTILE)
	{
		owner_.getComponent<HealthComponent>()->takeDamage(other.getComponent<DamageComponent>()->getDamage());
	}
}

void AIComponent::handleEvent(const ComponentEvent& e)
{
	if (e.getType() == ComponentEvent::Type::onDeath)
	{
		auto drop = e.getScene().gameObjects.add("Drop", "", owner_.getPos());
	}
}

Component::Type AIComponent::getType()
{
	return Component::Type::AI;
}



bool AIComponent::isNearby(float dist, float radius)
{
	return std::abs(dist) <= radius;
}

