#include "PlayerProjectileBuilder.h"

#include "Resources/Resources.h"
#include "Components/Render/SpriteRenderer.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "DamageComponent.h"
#include "DieOnCollision.h"


PlayerProjectileBuilder::PlayerProjectileBuilder()
{
}

PlayerProjectileBuilder::~PlayerProjectileBuilder()
{
}

std::shared_ptr<GameObject> PlayerProjectileBuilder::build(ComponentSystem& componentSystem, const std::string& name)
{
	auto newProjectile = std::make_shared<GameObject>();
	auto& projectileToBuild = *newProjectile;

	projectileToBuild.setType(GameObject::Type::PLAYER_PROJECTILE);
	projectileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(projectileToBuild, Resources::getSpriteSheet("Assets/Animations/playerProjectile.png")));
	auto physics = componentSystem.getNew<PhysicsComponent>(projectileToBuild);
	physics->enableGravity(false);
	projectileToBuild.addComponent(physics);
	projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 10));
	projectileToBuild.addComponent(componentSystem.getNew<DieOnCollision>(projectileToBuild));
	return newProjectile;
}
