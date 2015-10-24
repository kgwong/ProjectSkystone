#include "EnemyBuilder.h"

#include "Enemy.h"

#include "SpriteRenderer.h"
#include "BasicEnemyMovementComponent.h"

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
		enemyToBuild.setMovementComponent(std::shared_ptr<BasicEnemyMovementComponent>(new BasicEnemyMovementComponent(0)));
	}
	else if (enemyName == "TestMob1")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemy.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		enemyToBuild.setMovementComponent(std::shared_ptr<BasicEnemyMovementComponent>(new BasicEnemyMovementComponent()));
	}
	return &enemyToBuild;
}
