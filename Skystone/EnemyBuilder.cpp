#include "EnemyBuilder.h"

#include "TextureLoader.h"
#include "GameObject.h"

#include "SpriteRenderer.h"
#include "BasicEnemyMovementComponent.h"
#include "RandomJumperComponent.h"
#include "TrackerComponent.h"
#include "ColliderComponent.h"
#include "FallingAIComponent.h"
#include "HealthComponent.h"
#include "FlyingAIComponent.h"
#include "AIjump.h"
#include "SwingingAIComponent.h"
#include "SnakeAIComponent.h"
#include "PhysicsComponent.h"
#include "DamageComponent.h"

EnemyBuilder::EnemyBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}


EnemyBuilder::~EnemyBuilder()
{
}

std::shared_ptr<GameObject> EnemyBuilder::build(ComponentSystem& componentSystem, const std::string& enemyName)
{
	auto newEnemy = std::make_shared<GameObject>();
	auto& enemyToBuild = *newEnemy;
	enemyToBuild.setType(GameObject::Type::ENEMY);
	if (enemyName == "TestMobStrong")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemyStrong.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 500));
		enemyToBuild.addComponent(componentSystem.getNew<FallingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "TestMob1")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/enemy.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<TrackerComponent>(enemyToBuild));
	}
	else if (enemyName == "BasicEnemy")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/BasicEnemy.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<BasicEnemyMovementComponent>(enemyToBuild));

	}
	else if (enemyName == "RandomJumper")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/RandomJumper.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<RandomJumperComponent>(enemyToBuild));

	}
	else if (enemyName == "AIJump")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/AIJump.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<AIjump>(enemyToBuild));
	}
	else if (enemyName == "Flying")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/Flying.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<FlyingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "Coward")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/Coward.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 15));
		auto ai = componentSystem.getNew<TrackerComponent>(enemyToBuild);
		ai->setEnemyState(COWARD);
		enemyToBuild.addComponent(ai);
	}
	else if (enemyName == "swingmob")
	{
		TextureSheet* enemySprite = textureLoader_->getTextureSheet("Assets/Enemies/swingmob.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 65));
		enemyToBuild.addComponent(componentSystem.getNew<SwingingAIComponent>(enemyToBuild));
	}

	return newEnemy;
}
