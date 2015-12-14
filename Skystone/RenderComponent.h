#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject& owner)
		:Component(owner)
	{

	}
	virtual ~RenderComponent() {};

	int x() { return owner_.getPosX(); }
	int y() { return owner_.getPosY(); }

	virtual void start(Level& level) = 0;
	virtual void update(Level& level) = 0;

	virtual int getWidth() { return 0; }
	virtual int getHeight() { return 0; }

	virtual int getRenderLayer() 
	{ 
		switch (owner_.getType())
		{
		case EntityType::BACKGROUND:
		case EntityType::TILE:
			return 0;
		case EntityType::ENEMY:
		case EntityType::PLAYER_PROJECTILE:
		case EntityType::ENEMY_PROJECTILE:
		case EntityType::PICKUP:
			return 1;
		case EntityType::PLAYER:
			return 2;
		default:
			return 2;
		}
	}
};

#endif //RENDER_COMPONENT_H

