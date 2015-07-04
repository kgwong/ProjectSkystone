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

enum  Direction {UP, DOWN, LEFT, RIGHT} ; //

class Player : public CollidingObject,
			   public DamageableObject,
			   public PhysicalObject
{
public:
	Player(GameWindow* gw);
	~Player();

	void handleInput(SDL_Event &e);
	void handleInput2(); //

	void update(Level& level);
	void jump();
	void shoot();

	void handleCollisionX(CollidingObject& enemy);
	void handleCollisionY(CollidingObject& enemy);

	void draw();


private:
	static const int JUMP_VELOCITY = -20; //negative Y means up!

	Animation animation;
	bool grounded;

	SDL_Texture* test;//!!!!!!!!!!!

};

#endif //PLAYER_H

