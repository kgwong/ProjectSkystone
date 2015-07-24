#ifndef ENEMY_H
#define ENEMY_H

#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "GameWindow.h"
#include "Sprite.h"


struct LevelEntities;
class PhysicsComponent;

class Enemy : public GameObject
{
public:
	Enemy(GameWindow* gw, Sprite* sprite);
	~Enemy();

	void update(LevelEntities& entities);
	void render();

	void takeDamage(int damage);
	bool isDead();

	virtual std::string getName();
	virtual EntityType getType();
	virtual void onCollision(GameObject& other);

public: 
	ColliderComponent _colliderComponent;

private:
	Sprite* _sprite;
	HealthComponent _healthComponent;
	PhysicsComponent _physicsComponent;

};

#endif //ENEMY_H

