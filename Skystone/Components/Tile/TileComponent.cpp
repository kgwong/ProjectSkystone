#include "TileComponent.h"



TileComponent::TileComponent(GameObject& owner, Type type)
	:NonUpdatingComponent(owner), type_(type)
{
}

TileComponent::~TileComponent()
{
}

TileComponent::Type TileComponent::getTileType()
{
	return type_;
}
