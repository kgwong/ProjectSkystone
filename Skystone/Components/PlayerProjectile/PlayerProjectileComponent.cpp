#include "PlayerProjectileComponent.h"

#include "Components/Physics/PhysicsComponent.h"
#include "Application/Log.h"


PlayerProjectileComponent::PlayerProjectileComponent(GameObject& owner)
	: UpdatingComponent(owner)
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

void PlayerProjectileComponent::update(Scene & scene)
{
	if (!owner_.getPos().inBounds(scene.getWidth(), scene.getHeight()))
	{
		Point deadPos = owner_.getPos();
		owner_.kill();
		LOG("HARVEY") << "bullet killed at: " << deadPos;
	}

}
