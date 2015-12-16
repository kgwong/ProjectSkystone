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
		case GameObject::Type::BACKGROUND:
		case GameObject::Type::TILE:
			return 0;
		case GameObject::Type::ENEMY:
		case GameObject::Type::PLAYER_PROJECTILE:
		case GameObject::Type::ENEMY_PROJECTILE:
		case GameObject::Type::DROP:
			return 1;
		case GameObject::Type::PLAYER:
			return 2;
		default:
			return 2;
		}
	}
};

#endif //RENDER_COMPONENT_H

