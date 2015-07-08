#ifndef ENEMY_H
#define ENEMY_H

#include "CollidingObject.h"
#include "DamageableObject.h"
#include "PhysicalObject.h"
#include "GameWindow.h"
#include "Sprite.h"
#include "LevelEntities.h"

struct LevelEntities;

class Enemy : public CollidingObject,
			  public DamageableObject,
			  public PhysicalObject
{
public:
	Enemy(GameWindow* gw, Sprite* sprite);
	~Enemy();

	void update(LevelEntities& entities);
	void render();

private:
	Sprite* _sprite;

	void handleCollisionX(CollidingObject& other);
	void handleCollisionY(CollidingObject& other);
};

#endif //ENEMY_H

