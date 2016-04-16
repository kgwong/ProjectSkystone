#include "PlayerProjectileBuilder.h"

#include "Components/Render/SpriteRenderer.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Common/DieOnCollision.h"
#include "Components/PlayerProjectile/PlayerProjectileComponent.h"
#include "Components/Common/StickOnCollision.h"


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
	projectileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(projectileToBuild, "Assets/Animations/playerProjectile.png"));
	projectileToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 10));
	projectileToBuild.addComponent(componentSystem.getNew<DieOnCollision>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<PlayerProjectileComponent>(projectileToBuild));

	return newProjectile;
}
