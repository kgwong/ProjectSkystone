#include "AIComponent.h"

#include "Components/Common/HealthComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Render/SpriteRenderer.h"

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

void AIComponent::handleEvent(const OnDeathEvent & e)
{
	auto drop = e.getScene().gameObjects.add("Drop", "", owner_.getPos());
}

Component::Type AIComponent::getType()
{
	return Component::Type::AI;
}



bool AIComponent::isNearby(float dist, float radius)
{
	return std::abs(dist) <= radius;
}

void AIComponent::fireProjectile(float xDist, float yDist, float playerSide, float offset, Scene& scene, float speed)
{
	auto bullet = scene.gameObjects.add("EnemyProjectile", "AcidProjectile", owner_.getPos() + Point(0, 25));
	auto bullet_physics = bullet->getComponent<PhysicsComponent>();
	float newVelX = speed * playerSide;
	bullet_physics->setVelX(newVelX * 60.0f);
	bullet_physics->setVelY((newVelX * yDist / xDist + offset) * 60.0f);
	bullet->getComponent<SpriteRenderer>()->setRotation(atan((newVelX * yDist / xDist + offset) / newVelX) * 180 / 3.14159265359);

}