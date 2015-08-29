#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "GameWindow.h"
#include "Direction.h"
#include "Block.h"

#include "RenderComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "TextureLoader.h"

class Level;
class PhysicsComponent;
class PlayerState;

class Player : public GameObject
{

public:
	Player(TextureLoader* textureLoader);
	~Player();

	void handleInput(SDL_Event &e);
	void handleInput2(); //

	void update(Level& Level);
	void render();

	void changeState(PlayerState* state);
	void jump();
	void shoot(Level& level);

	virtual std::string getName() const;
	virtual EntityType getType() const;
	virtual void onCollision(CollisionInfo& collision);

public:
	static const int JUMP_VELOCITY = -20; //negative Y means up!
	static const int WALK_VELOCITY = 5; 

private:
	std::shared_ptr<RenderComponent> _renderComponent;
	std::shared_ptr<HealthComponent> _healthComponent;
	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<ColliderComponent> _colliderComponent;

	Block _oldBlock;
	Point _oldPosInBlock;

	Direction dir; 

	bool _shoot;

	PlayerState* currState_;
};

#endif //PLAYER_H

