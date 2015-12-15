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
		case ObjectType::BACKGROUND:
		case ObjectType::TILE:
			return 0;
		case ObjectType::ENEMY:
		case ObjectType::PLAYER_PROJECTILE:
		case ObjectType::ENEMY_PROJECTILE:
		case ObjectType::DROP:
			return 1;
		case ObjectType::PLAYER:
			return 2;
		default:
			return 2;
		}
	}
};

#endif //RENDER_COMPONENT_H

