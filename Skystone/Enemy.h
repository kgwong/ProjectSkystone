#ifndef ENEMY_H
#define ENEMY_H

#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "AIComponent.h"

class Level;
class PhysicsComponent;

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Point position);
	Enemy(int x, int y);
	virtual ~Enemy();

	void update(Level& level);
	void render(Level& level); // temporary

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
	std::shared_ptr<AIComponent> _movementComponent;

public:
	void setRenderComponent(std::shared_ptr<RenderComponent> renderComponent);
	void setHealthComponent(std::shared_ptr<HealthComponent> healthComponent);
	void setMovementComponent(std::shared_ptr<AIComponent> movementComponent);

};

#endif //ENEMY_H

