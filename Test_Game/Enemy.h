#ifndef ENEMY_H
#define ENEMY_H

#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "EnemyBuilder.h"

#include "GameWindow.h"
#include "Sprite.h"

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

	void takeDamage(int damage);
	bool isDead();

	virtual std::string getName();
	virtual Component* getComponent(ComponentType type);
	virtual EntityType getType() const;
	virtual void onCollision(CollisionInfo& collision);
	virtual void onDeath(Level& level);

private:
	std::shared_ptr<RenderComponent> _renderComponent;
	std::shared_ptr<HealthComponent> _healthComponent;
	PhysicsComponent _physicsComponent;
	ColliderComponent _colliderComponent;

private:
	void setRenderComponent(RenderComponent* renderComponent);
	void setHealthComponent(HealthComponent* healthComponent);

};

#endif //ENEMY_H

