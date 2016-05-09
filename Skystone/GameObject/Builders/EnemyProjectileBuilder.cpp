#include "EnemyProjectileBuilder.h"

#include "Components/Render/SpriteRenderer.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Common/DamageComponent.h"
#include "Components/Common/DieOnCollision.h"
#include "Components/EnemyProjectile/EnemyProjectileComponent.h"
#include "Components/Common/StickOnCollision.h"

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

	if (name == "AcidProjectile")
	{

		projectileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(projectileToBuild, "Assets/Animations/acidprojectile.png"));
		projectileToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 5));
		projectileToBuild.addComponent(componentSystem.getNew<DieOnCollision>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<EnemyProjectileComponent>(projectileToBuild));

	}
	else if (name == "ClawProjectile")
	{

		projectileToBuild.setType(GameObject::Type::ENEMY);
		projectileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(projectileToBuild, "Assets/Animations/acidprojectile.png"));
		projectileToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 20));
		projectileToBuild.addComponent(componentSystem.getNew<EnemyProjectileComponent>(projectileToBuild));


	}
	else if (name == "LazerProjectile")
	{

		projectileToBuild.setType(GameObject::Type::ENEMY_PROJECTILE);
		projectileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(projectileToBuild, "Assets/Animations/acidprojectile.png"));
		projectileToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 1));
		projectileToBuild.addComponent(componentSystem.getNew<EnemyProjectileComponent>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<DieOnCollision>(projectileToBuild));
		projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));


	}
	return newProjectile;
}
