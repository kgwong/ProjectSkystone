#include "TileBuilder.h"

#include "Game/GameConstants.h"
#include "Components/Collider/ColliderComponent.h"

#include "Resources/Resources.h"
#include "Components/Render/TileRenderer.h"
#include "Components/Tile/TileComponent.h"
#include "Liftcomponent.h"

TileBuilder::TileBuilder()
{
}


TileBuilder::~TileBuilder()
{
}

GameObject& TileBuilder::build(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild)
{
	tileToBuild.setType(GameObject::Type::TILE);
	SpriteSheet* tileSet = Resources::getSpriteSheet("Assets/TileSets/bw.png");
	tileToBuild.addComponent(componentSystem.getNew<TileComponent>(tileToBuild, static_cast<TileComponent::Type>(tileType)));
	
	if (tileType == 1)
	{
		tileToBuild.addComponent(componentSystem.getNew<TileRenderer>(tileToBuild, tileSet, tileType));
		tileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(tileToBuild, 0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE));
	}
	else if (tileType == 2)
	{
		tileToBuild.addComponent(componentSystem.getNew<TileRenderer>(tileToBuild, tileSet, 1));
		tileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(tileToBuild, 0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE));
		tileToBuild.addComponent(componentSystem.getNew<LiftComponent>(tileToBuild));
	}
	return tileToBuild;
}