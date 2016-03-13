#include "PlayerProjectileComponent.h"

#include "Components/Physics/PhysicsComponent.h"


PlayerProjectileComponent::PlayerProjectileComponent(GameObject& owner)
	: NonUpdatingComponent(owner)
{
}


PlayerProjectileComponent::~PlayerProjectileComponent()
{
}

void PlayerProjectileComponent::start(Scene& scene)
{
	PhysicsComponent* physics = owner_.getComponent<PhysicsComponent>();
	physics->enableGravity(false);
}
