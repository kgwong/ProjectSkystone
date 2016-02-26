#include "SpecialTileComponent.h"
#include "Components/Physics/PhysicsComponent.h"



SpecialTileComponent::SpecialTileComponent(GameObject & owner):
	UpdatingComponent(owner)
{
}


SpecialTileComponent::~SpecialTileComponent()
{
}



bool SpecialTileComponent::isNearby(int dist, int radius)
{
	return std::abs(dist) <= radius;
}
