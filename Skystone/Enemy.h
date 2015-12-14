#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include "GameObject.h"

class Level;
class PhysicsComponent;
class HealthComponent;
class ColliderComponent;
class RenderComponent;
class AIComponent;
class DamageComponent;

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Point position);
	Enemy(int x, int y);
	virtual ~Enemy();

	void update(Level& level);

	virtual std::string getName();
	virtual EntityType getType() const;
	virtual void onCollision(CollisionInfo& collision);
	virtual void onDeath(Level& level);

private:
	std::shared_ptr<HealthComponent> _healthComponent;
	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<ColliderComponent> _colliderComponent;
	std::shared_ptr<AIComponent> _movementComponent;
	std::shared_ptr<DamageComponent> damageComponent_;

public:
	void setHealthComponent(std::shared_ptr<HealthComponent> healthComponent);
	void setMovementComponent(std::shared_ptr<AIComponent> movementComponent);
	void setColliderComponent(std::shared_ptr<ColliderComponent> component);


};

#endif //ENEMY_H

