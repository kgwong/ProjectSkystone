#include "TileComponent.h"



TileComponent::TileComponent(GameObject& owner, Type type)
	:Component(owner), type_(type)
{
}

TileComponent::~TileComponent()
{
}

TileComponent::Type TileComponent::getType()
{
	return type_;
}
