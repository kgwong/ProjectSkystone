#include "PlayerProjectileBuilder.h"

#include "PlayerProjectile.h"
#include "TextureLoader.h"
#include "AnimationRenderer.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "DamageComponent.h"

#include <memory>


PlayerProjectileBuilder::PlayerProjectileBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}

PlayerProjectileBuilder::~PlayerProjectileBuilder()
{
}

PlayerProjectile& PlayerProjectileBuilder::build(ComponentSystem& componentSystem, const std::string& name, PlayerProjectile& projectileToBuild)
{
	projectileToBuild.setType(ObjectType::PLAYER_PROJECTILE);
	projectileToBuild.addComponent(componentSystem.getNewRenderer<AnimationRenderer>(projectileToBuild, textureLoader_->getTextureSheet("Assets/Animations/playerProjectile.png")));
	projectileToBuild.addComponent(componentSystem.getNewPhysics<PhysicsComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNewNonUpdating<ColliderComponent>(projectileToBuild));
	projectileToBuild.addComponent(componentSystem.getNewNonUpdating<DamageComponent>(projectileToBuild, 10));
	return projectileToBuild;
}
