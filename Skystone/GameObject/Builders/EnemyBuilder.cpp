#include "EnemyBuilder.h"

#include "Resources/Resources.h"
#include "GameObject/GameObject.h"

#include "Components/Render/SpriteRenderer.h"
#include "Components/AI/BasicEnemyMovementComponent.h"
#include "Components/AI/RandomJumperComponent.h"
#include "Components/AI/TrackerComponent.h"
#include "Components/AI/FallingAIComponent.h"
#include "Components/AI/FlyingAIComponent.h"
#include "Components/AI/AIjump.h"
#include "Components/AI/SwingingAIComponent.h"
#include "Components/AI/SnakeAIComponent.h"
#include "Components/AI/PounceAIComponent.h"
#include "Components/AI/AlligatorAIComponent.h"
#include "Components/AI/BossAIComponent.h"

#include "Components/Common/DamageComponent.h"
#include "Components/Common/HealthComponent.h"

#include "Components/Physics/PhysicsComponent.h"
#include "Components/Collider/ColliderComponent.h"


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
		//SpriteSheet* enemySprite = Resources::getSpriteSheet("Images/gator cycle.png");
		//SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/RandomJumper.png");
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Images/birdmanruncycle.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<PounceAIComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 100));
	}
	else if (enemyName == "TestMob2")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Images/birdmanruncycle.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 10000));
		//enemyToBuild.addComponent(componentSystem.getNew<BasicEnemyMovementComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<BossAIComponent>(enemyToBuild));
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
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Images/stalin_4_turtle.png");
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
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 150));
		auto ai = componentSystem.getNew<TrackerComponent>(enemyToBuild);
		ai->setEnemyState(COWARD);
		enemyToBuild.addComponent(ai);
	}
	else if (enemyName == "swingmob")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Images/spooder.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 120));
		enemyToBuild.addComponent(componentSystem.getNew<SwingingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "Wallclimber")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Assets/Enemies/Wallclimber.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 1000));
		enemyToBuild.addComponent(componentSystem.getNew<SwingingAIComponent>(enemyToBuild));
	}
	else if (enemyName == "Gator")
	{
		SpriteSheet* enemySprite = Resources::getSpriteSheet("Images/gator cycle.png");
		enemyToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(enemyToBuild, enemySprite));
		enemyToBuild.addComponent(componentSystem.getNew<ColliderComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(enemyToBuild));
		enemyToBuild.addComponent(componentSystem.getNew<DamageComponent>(enemyToBuild, 10));
		enemyToBuild.addComponent(componentSystem.getNew<HealthComponent>(enemyToBuild, 600));
		enemyToBuild.addComponent(componentSystem.getNew<AlligatorAIComponent>(enemyToBuild));
	}
	return newEnemy;
}
