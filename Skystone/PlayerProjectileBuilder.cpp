#include "PlayerProjectileBuilder.h"

#include "PlayerProjectile.h"
#include "TextureLoader.h"
#include "AnimationRenderer.h"
#include "ColliderComponent.h"

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
	projectileToBuild.addComponent(componentSystem.getNewRenderer<AnimationRenderer>(projectileToBuild, textureLoader_->getTextureSheet("Assets/Animations/playerProjectile.png")));
	projectileToBuild.setColliderComponent(std::make_shared<ColliderComponent>(projectileToBuild));
	return projectileToBuild;
}
