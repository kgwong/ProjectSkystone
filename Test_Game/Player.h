#ifndef PLAYER_H
#define PLAYER_H

#include "GameWindow.h"
#include "GameObject.h"
#include "Animation.h"
#include "CollidingObject.h"
#include "DamageableObject.h"
#include "PhysicalObject.h"
#include "Direction.h"



#include "LevelEntities.h"


#include "RenderComponent.h"

class RenderComponent;
struct LevelEntities;

class Player : public CollidingObject,
			   public DamageableObject,
			   public PhysicalObject
{

public:
	Player(GameWindow* gw);
	~Player();

	void handleInput(SDL_Event &e);
	void handleInput2(); //

	void update(LevelEntities& entities);
	void jump();
	void shoot(LevelEntities& entities);

	void handleCollisionX(CollidingObject& enemy);
	void handleCollisionY(CollidingObject& enemy);

	void render();


private:
	static const int JUMP_VELOCITY = -20; //negative Y means up!

	RenderComponent _renderComponent;

	Animation _animation;
	Animation projectileAnimation;

	Direction dir; 

	bool _shoot;


	SDL_Texture* test;//!!!!!!!!!!!

};

#endif //PLAYER_H

