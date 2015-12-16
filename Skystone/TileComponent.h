#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "Component.h"

class TileComponent : public Component
{
public:
	enum Type
	{
		EMPTY = 0,
		SOLID = 1	
	};

public:
	TileComponent(GameObject& owner, Type type);
	virtual ~TileComponent();

	Type getType();

private:
	Type type_;
};

#endif //TIME_COMPONENT_H
