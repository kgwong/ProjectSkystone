#include "BossClawProjectileBuilder.h"

#include "Resources/Resources.h"
#include "Components/Render/SpriteRenderer.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Common/DieOnCollision.h"
#include "Components/EnemyProjectile/EnemyProjectileComponent.h"
#include "Components/Common/StickOnCollision.h"


BossClawProjectileBuilder::BossClawProjectileBuilder()
{
}


BossClawProjectileBuilder::~BossClawProjectileBuilder()
{
}

std::shared_ptr<GameObject> BossClawProjectileBuilder::build(ComponentSystem& componentSystem, const std::string& name)
{
	auto newProjectile = std::make_shared<GameObject>();
	auto& projectileToBuild = *newProjectile;

	projectileToBuild.setType(GameObject::Type::ENEMY_PROJECTILE);
	projectileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(projectileToBuild, Resources::getSpriteSheet("Assets/Animations/acidprojectile.png")));
	projectileToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 20));
	projectileToBuild.addComponent(componentSystem.getNew<EnemyProjectileComponent>(projectileToBuild));

	return newProjectile;
}