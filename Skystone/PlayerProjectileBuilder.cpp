#include "PlayerProjectileBuilder.h"

#include "PlayerProjectile.h"
#include "TextureLoader.h"
#include "AnimationRenderer.h"

#include <memory>


PlayerProjectileBuilder::PlayerProjectileBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}

PlayerProjectileBuilder::~PlayerProjectileBuilder()
{
}

PlayerProjectile& PlayerProjectileBuilder::build(const std::string& name, PlayerProjectile& projectileToBuild)
{
	projectileToBuild.setRenderComponent(std::make_shared<AnimationRenderer>(textureLoader_->getTextureSheet("Assets/Animations/playerProjectile.png")));
	return projectileToBuild;
}
