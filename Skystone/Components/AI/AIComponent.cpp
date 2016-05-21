#include "AIComponent.h"

#include "Components/Common/HealthComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Render/SpriteRenderer.h"
#define SPEED 60.0f

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
		if(owner_.getComponent<HealthComponent>() != nullptr)
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

void AIComponent::fireProjectileDirection(float xDist, float yDist, float playerSide, float offset, Scene& scene, float speed, int position)
{	//if you 
	//the offset pushes the projectile up (-) or down (+)
	//xDist and yDist are distance from target; they dictate the direction
	//position determines where the projectile shoots out from (it is only for y)

	auto bullet = scene.gameObjects.add("EnemyProjectile", "AcidProjectile", owner_.getPos() + Point(0, position));
	auto bullet_physics = bullet->getComponent<PhysicsComponent>();
	float newVelX = speed * playerSide;

	bullet_physics->setVelX(newVelX * SPEED);
	bullet_physics->setVelY((newVelX * yDist / xDist + offset) * SPEED);
	bullet->getComponent<SpriteRenderer>()->setRotation(atan((newVelX * yDist / xDist + offset) / newVelX) * 180 / 3.14159265359);

}

std::shared_ptr<GameObject> AIComponent::fireProjectile(float xSpeed, float ySpeed, Scene& scene, int degrees, int positionX, int positionY, std::string attack)
{
	auto bullet = scene.gameObjects.add("EnemyProjectile", attack, owner_.getPos() + Point(0, positionY) + Point(positionX, 0));
	auto bullet_physics = bullet->getComponent<PhysicsComponent>();
	
	bullet_physics->setVelX(xSpeed * SPEED);
	bullet_physics->setVelY(ySpeed * SPEED);
	bullet->getComponent <SpriteRenderer>()->setRotation(degrees);
	return bullet;
}