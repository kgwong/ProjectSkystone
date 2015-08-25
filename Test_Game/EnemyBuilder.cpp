#include "EnemyBuilder.h"

#include "Enemy.h"

#include "SpriteRenderer.h"

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
		TextureSheet* enemySprite = _resourceLocator->getTextureSheet("Assets/Enemies/enemyStrong.png");
		enemy->setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemy->setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(500)));
	}
	else if (enemyName == "TestMob1")
	{
		TextureSheet* enemySprite = _resourceLocator->getTextureSheet("Assets/Enemies/enemy.png");
		enemy->setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(enemySprite)));
		enemy->setHealthComponent(std::shared_ptr<HealthComponent>(new HealthComponent(100)));
	}
	return enemy;
}
