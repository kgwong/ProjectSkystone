#ifndef PLAYER_H
#define PLAYER_H

#include "GameWindow.h"
#include "Animation.h"
#include "Direction.h"

#include "RenderComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

struct LevelEntities;
class PhysicsComponent;

class Player : public GameObject
{

public:
	Player(GameWindow* gw);
	~Player();

	void handleInput(SDL_Event &e);
	void handleInput2(); //

	void update(LevelEntities& entities);
	void jump();
	void shoot(LevelEntities& entities);

	virtual Component* getComponent(const std::string& componentName);
	virtual std::string getName() const;
	virtual EntityType getType() const;
	virtual void onCollision(GameObject& other);

	void render();

private:
	static const int JUMP_VELOCITY = -20; //negative Y means up!

	GameWindow* _gw;
	RenderComponent _renderComponent;
	HealthComponent _healthComponent;
	PhysicsComponent _physicsComponent;
	ColliderComponent _colliderComponent;

	Animation _animation;
	Animation projectileAnimation;

	Direction dir; 

	bool _shoot;

};

#endif //PLAYER_H

