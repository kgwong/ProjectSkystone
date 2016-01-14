#include "PlayerProjectileBuilder.h"

#include "TextureLoader.h"
#include "AnimationRenderer.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "DamageComponent.h"
#include "DieOnCollision.h"


PlayerProjectileBuilder::PlayerProjectileBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
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
	projectileToBuild.addComponent(componentSystem.getNew<AnimationRenderer>(projectileToBuild, textureLoader_->getTextureSheet("Assets/Animations/playerProjectile.png")));
	projectileToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNew<DamageComponent>(projectileToBuild, 10));
	projectileToBuild.addComponent(componentSystem.getNew<DieOnCollision>(projectileToBuild));
	return newProjectile;
}
