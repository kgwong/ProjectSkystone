#include "EnemyBuilder.h"

#include "TextureLoader.h"
#include "Enemy.h"

#include "SpriteRenderer.h"
#include "BasicEnemyMovementComponent.h"
#include "RandomJumperComponent.h"
#include "TrackerComponent.h"
#include "ColliderComponent.h"
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

Enemy& EnemyBuilder::build(ComponentSystem& componentSystem, const std::string& enemyName, Enemy& enemyToBuild)
{
	if (enemyName == "TestMobStrong")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemyStrong.png");
		enemyToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.setColliderComponent(std::make_shared<ColliderComponent>(enemyToBuild));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(enemyToBuild, 500)));
		//enemyToBuild.setMovementComponent(std::shared_ptr<FallingAIComponent>(new FallingAIComponent(enemyToBuild)));
		enemyToBuild.addComponent(componentSystem.getNewAI<FallingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "TestMob1")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemy.png");
		enemyToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.setColliderComponent(std::make_shared<ColliderComponent>(enemyToBuild));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(enemyToBuild, 100)));
		//enemyToBuild.setMovementComponent(std::shared_ptr<TrackerComponent>(new TrackerComponent()));
		enemyToBuild.addComponent(componentSystem.getNewAI<TrackerComponent>(enemyToBuild));
	}
	else if (enemyName == "BasicEnemy")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/BasicEnemy.png");
		enemyToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.setColliderComponent(std::make_shared<ColliderComponent>(enemyToBuild));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(enemyToBuild, 100)));
		//enemyToBuild.setMovementComponent(std::make_shared<BasicEnemyMovementComponent>());
		enemyToBuild.addComponent(componentSystem.getNewAI<BasicEnemyMovementComponent>(enemyToBuild));

	}
	else if (enemyName == "RandomJumper")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/RandomJumper.png");
		enemyToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.setColliderComponent(std::make_shared<ColliderComponent>(enemyToBuild));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(enemyToBuild, 100)));
		//enemyToBuild.setMovementComponent(std::make_shared<RandomJumperComponent>());
		enemyToBuild.addComponent(componentSystem.getNewAI<RandomJumperComponent>(enemyToBuild));

	}
	else if (enemyName == "AIJump")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/AIJump.png");
		enemyToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.setColliderComponent(std::make_shared<ColliderComponent>(enemyToBuild));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(enemyToBuild, 100)));
		//enemyToBuild.setMovementComponent(std::make_shared<AIjump>());
		enemyToBuild.addComponent(componentSystem.getNewAI<AIjump>(enemyToBuild));
	}
	else if (enemyName == "Flying")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/Flying.png");
		enemyToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.setColliderComponent(std::make_shared<ColliderComponent>(enemyToBuild));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(enemyToBuild, 100)));
		//enemyToBuild.setMovementComponent(std::make_shared<FlyingAIComponent>());
		enemyToBuild.addComponent(componentSystem.getNewAI<FlyingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "Coward")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/Coward.png");
		enemyToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.setColliderComponent(std::make_shared<ColliderComponent>(enemyToBuild));
		enemyToBuild.setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(enemyToBuild, 100)));
		auto ai = componentSystem.getNewAI<TrackerComponent>(enemyToBuild);
		ai->setEnemyState(COWARD);
		enemyToBuild.addComponent(ai);
	}
	return enemyToBuild;
}
