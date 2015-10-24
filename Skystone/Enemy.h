#ifndef ENEMY_H
#define ENEMY_H

#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "BasicEnemyMovementComponent.h"

#include "EnemyBuilder.h"

#include "GameWindow.h"

class Level;
class PhysicsComponent;

class Enemy : public GameObject
{
	friend  EnemyBuilder;

public:
	Enemy();
	virtual ~Enemy();

	void update(Level& level);
	void render();

	bool isDead();

	virtual std::string getName();
	virtual EntityType getType() const;
	virtual void onCollision(CollisionInfo& collision);
	virtual void onDeath(Level& level);

private:
	std::shared_ptr<RenderComponent> _renderComponent;
	std::shared_ptr<HealthComponent> _healthComponent;
	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<ColliderComponent> _colliderComponent;
	std::shared_ptr<BasicEnemyMovementComponent> _movementComponent;

private:
	void setRenderComponent(std::shared_ptr<RenderComponent> renderComponent);
	void setHealthComponent(std::shared_ptr<HealthComponent> healthComponent);
	void setMovementComponent(std::shared_ptr<BasicEnemyMovementComponent> movementComponent);

};

#endif //ENEMY_H

