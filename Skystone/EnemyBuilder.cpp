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
#include "AIjump.h"

EnemyBuilder::EnemyBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}


EnemyBuilder::~EnemyBuilder()
{
}

Enemy& EnemyBuilder::build(const std::string& enemyName, Enemy& enemyToBuild)
{
	if (enemyName == "TestMobStrong")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemyStrong.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(500)));
		//enemyToBuild.setMovementComponent(std::shared_ptr<BasicEnemyMovementComponent>(new BasicEnemyMovementComponent(0)));
		//enemyToBuild.setMovementComponent(std::shared_ptr<TrackerComponent>(new TrackerComponent()));
		enemyToBuild.setMovementComponent(std::shared_ptr<FallingAIComponent>(new FallingAIComponent()));
		//enemyToBuild.setMovementComponent(std::shared_ptr<AIjump>(new AIjump()));
	}
	else if (enemyName == "TestMob1")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemy.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		//enemyToBuild.setMovementComponent(std::shared_ptr<RandomJumperComponent>(new RandomJumperComponent()));
		//enemyToBuild.setMovementComponent(std::shared_ptr<FlyingAIComponent>(new FlyingAIComponent()));
		enemyToBuild.setMovementComponent(std::shared_ptr<TrackerComponent>(new TrackerComponent()));
	}
	else if (enemyName == "BasicEnemy")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/BasicEnemy.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		enemyToBuild.setMovementComponent(std::make_shared<BasicEnemyMovementComponent>());
	}
	else if (enemyName == "RandomJumper")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/RandomJumper.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		enemyToBuild.setMovementComponent(std::make_shared<RandomJumperComponent>());
	}
	else if (enemyName == "AIJump")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/AIJump.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		enemyToBuild.setMovementComponent(std::make_shared<AIjump>());
	}
	else if (enemyName == "Flying")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/Flying.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		enemyToBuild.setMovementComponent(std::make_shared<FlyingAIComponent>());
	}
	else if (enemyName == "Coward")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/Coward.png");
		enemyToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
		std::shared_ptr<TrackerComponent> ai = std::make_shared<TrackerComponent>();
		ai->setEnemyState(COWARD);
		enemyToBuild.setMovementComponent(ai);
	}
	return enemyToBuild;
}
