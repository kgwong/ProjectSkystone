#include "EnemyBuilder.h"

#include "Enemy.h"

#include "StaticSpriteRenderer.h"

EnemyBuilder::EnemyBuilder(ResourceLocator* resourceLocator)
	:_resourceLocator(resourceLocator)
{
}


EnemyBuilder::~EnemyBuilder()
{
}

Enemy* EnemyBuilder::create(const std::string& enemyName)
{
	Enemy* enemy = new Enemy();
	if (enemyName == "TestMobStrong")
	{
		Sprite* enemySprite = _resourceLocator->getSprite("Assets/Enemies/enemyStrong.png");
		enemy->setRenderComponent(new StaticSpriteRenderer(enemySprite));
		enemy->setHealthComponent(new HealthComponent(500));
		enemy->setWidth(enemySprite->getWidth());
		enemy->setHeight(enemySprite->getHeight());
	}
	else if (enemyName == "TestMob1")
	{
		Sprite* enemySprite = _resourceLocator->getSprite("Assets/Enemies/enemy.png");
		enemy->setRenderComponent(new StaticSpriteRenderer(enemySprite));
		enemy->setHealthComponent(new HealthComponent(100));
		enemy->setWidth(enemySprite->getWidth());
		enemy->setHeight(enemySprite->getHeight());
	}
	return enemy;
}
