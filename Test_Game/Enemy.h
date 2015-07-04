#ifndef ENEMY_H
#define ENEMY_H

#include "CollidingObject.h"
#include "DamageableObject.h"
#include "GameWindow.h"
#include "Sprite.h"

class Enemy : public CollidingObject,
			  public DamageableObject
{
public:
	Enemy(GameWindow* gw, Sprite* sprite);
	~Enemy();

	void draw();

private:
	Sprite* _sprite;
};

#endif //ENEMY_H

