#include "EnemyBuilder.h"

#include "Resources/Resources.h"
#include "GameObject.h"

#include "Components/Render/SpriteRenderer.h"
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
#include "PounceAIComponent.h"

EnemyBuilder::EnemyBuilder()
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
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/enemyStrong.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 500));
		enemyToBuild.addComponent(componentSystem.getNew<FallingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "TestMob1")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/enemy.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<PounceAIComponent>(enemyToBuild));
	}
	else if (enemyName == "BasicEnemy")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/BasicEnemy.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<BasicEnemyMovementComponent>(enemyToBuild));

	}
	else if (enemyName == "RandomJumper")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/RandomJumper.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<RandomJumperComponent>(enemyToBuild));

	}
	else if (enemyName == "AIJump")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/AIJump.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<AIjump>(enemyToBuild));
	}
	else if (enemyName == "Flying")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/Flying.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
		enemyToBuild.addComponent(componentSystem.getNew<FlyingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "Coward")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/Coward.png");
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
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/swingmob.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 120));
		enemyToBuild.addComponent(componentSystem.getNew<SwingingAIComponent>(enemyToBuild));
	}

	return newEnemy;
}
