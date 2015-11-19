#include "EnemyBuilder.h"

#include "TextureLoader.h"
#include "Enemy.h"

#include "SpriteRenderer.h"
#include "BasicEnemyMovementComponent.h"
#include "RandomJumperComponent.h"
#include "TrackerComponent.h"
#include "FallingAIComponent.h"
#include "HealthComponent.h"
#include "FlyingAIComponent.h"

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
		//enemyToBuild.setMovementComponent(std::shared_ptr<BasicEnemyMovementComponent>(new BasicEnemyMovementComponent(0)));
		//enemyToBuild.setMovementComponent(std::shared_ptr<TrackerComponent>(new TrackerComponent()));
		enemyToBuild.setMovementComponent(std::shared_ptr<FallingAIComponent>(new FallingAIComponent()));

	}
	else if (enemyName == "TestMob1")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemy.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		//enemyToBuild.setMovementComponent(std::shared_ptr<RandomJumperComponent>(new RandomJumperComponent()));
		enemyToBuild.setMovementComponent(std::shared_ptr<FlyingAIComponent>(new FlyingAIComponent()));
	}
	//enemyToBuild.callStartOnComponents(); //
	return &enemyToBuild;
}
