#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "Components/NonUpdatingComponent.h"

class TileComponent : public NonUpdatingComponent
{
public:
	//warning: no longer accurate
	enum Type
	{
		EMPTY = 0,
		SOLID = 1,
		LIFT = 2,
		BURN = 3
	};

public:
	TileComponent(GameObject& owner, Type type);
	virtual ~TileComponent();

	//warning: no longer accurate
	Type getTileType();

private:
	Type type_;
};

#endif //TIME_COMPONENT_H
