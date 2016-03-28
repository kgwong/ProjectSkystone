#include "EnemyProjectileComponent.h"

#include "Components/Physics/PhysicsComponent.h"

EnemyProjectileComponent::EnemyProjectileComponent(GameObject& owner)
	: NonUpdatingComponent(owner)
{
}


EnemyProjectileComponent::~EnemyProjectileComponent()
{
}

void EnemyProjectileComponent::start(Scene& scene)
{
	PhysicsComponent * physics = owner_.getComponent<PhysicsComponent>();
	physics->enableGravity(false);
}