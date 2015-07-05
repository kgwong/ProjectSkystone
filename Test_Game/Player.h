#ifndef PLAYER_H
#define PLAYER_H

#include "GameWindow.h"
#include "GameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "CollidingObject.h"
#include "DamageableObject.h"
#include "PhysicalObject.h"
#include "Enemy.h"
#include "Level.h"
#include "PlayerProjectile.h"
#include "Direction.h"

class Player : public CollidingObject,
			   public DamageableObject,
			   public PhysicalObject
{

public:
	Player(GameWindow* gw);
	~Player();

	void setLevel(Level* level);

	void handleInput(SDL_Event &e);
	void handleInput2(); //

	void update();
	void jump();
	void shoot();

	void handleCollisionX(CollidingObject& enemy);
	void handleCollisionY(CollidingObject& enemy);

	void draw();


private:
	static const int JUMP_VELOCITY = -20; //negative Y means up!

	Animation animation;
	Animation projectileAnimation;

	Direction dir; 

	bool grounded;

	Level* currLevel;

	SDL_Texture* test;//!!!!!!!!!!!

};

#endif //PLAYER_H

