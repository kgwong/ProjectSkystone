#ifndef SPECIAL_TILE_COMPONENT_H
#define SPECIAL_TILE_COMPONENT_H

#include "Components/UpdatingComponent.h"
#include "GameTypes/Point.h"

class PhysicsComponent;

class SpecialTileComponent :
	public UpdatingComponent
{
public:
	SpecialTileComponent(GameObject& owner);
	virtual ~SpecialTileComponent();



	static bool isNearby(int dist, int radius);
};

#endif //#SPECIAL_TILE_COMPONENT_H