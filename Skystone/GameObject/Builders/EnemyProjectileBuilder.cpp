#include "EnemyProjectileBuilder.h"

#include "Resources/Resources.h"
#include "Components/Render/SpriteRenderer.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Common/DieOnCollision.h"
#include "Components/EnemyProjectile/EnemyProjectileComponent.h"
#include "StickOnCollision.h"

EnemyProjectileBuilder::EnemyProjectileBuilder()
{
}


EnemyProjectileBuilder::~EnemyProjectileBuilder()
{
}

std::shared_ptr<GameObject> EnemyProjectileBuilder::build(ComponentSystem& componentSystem, const std::string& name)
{
	auto newProjectile = std::make_shared<GameObject>();
	auto& projectileToBuild = *newProjectile;

	projectileToBuild.setType(GameObject::Type::ENEMY_PROJECTILE);
	projectileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(projectileToBuild, Resources::getSpriteSheet("Assets/Animations/playerProjectile.png")));
	projectileToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 5));
	projectileToBuild.addComponent(componentSystem.getNew<DieOnCollision>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<EnemyProjectileComponent>(projectileToBuild));

	return newProjectile;
}
