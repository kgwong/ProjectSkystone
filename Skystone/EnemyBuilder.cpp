#include "EnemyBuilder.h"

#include "Enemy.h"

#include "SpriteRenderer.h"

EnemyBuilder::EnemyBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}


EnemyBuilder::~EnemyBuilder()
{
}

Enemy* EnemyBuilder::build(const std::string& enemyName, Enemy& enemyToBuild)
{
	if (enemyName == "TestMobStrong")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemyStrong.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(500)));
	}
	else if (enemyName == "TestMob1")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemy.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
	}
	return &enemyToBuild;
}
