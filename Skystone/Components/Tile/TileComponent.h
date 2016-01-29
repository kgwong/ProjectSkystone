#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "Components/NonUpdatingComponent.h"

class TileComponent : public NonUpdatingComponent
{
public:
	enum Type
	{
		EMPTY = 0,
		SOLID = 1,
		FLOAT = 2
	};

public:
	TileComponent(GameObject& owner, Type type);
	virtual ~TileComponent();

	Type getTileType();

private:
	Type type_;
};

#endif //TIME_COMPONENT_H
