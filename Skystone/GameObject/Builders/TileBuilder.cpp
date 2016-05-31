#include "TileBuilder.h"

#include "Game/GameConstants.h"
#include "Components/Collider/ColliderComponent.h"

#include "Resources/Resources.h"
#include "Components/Render/TileRenderer.h"
#include "Components/Render/SpriteRenderer.h"
#include "Components/Tile/TileComponent.h"
#include "Components/Tile/LiftTileComponent.h"
#include "Components/Tile/BurnTileComponent.h"
#include "Components/Common/DamageComponent.h"

TileBuilder::TileBuilder()
{
}


TileBuilder::~TileBuilder()
{
}

GameObject& TileBuilder::build(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild)
{
	tileToBuild.setType(GameObject::Type::TILE);
	SpriteSheet* tileSet = Resources::getSpriteSheet("Images/Baseblock.png");
	tileToBuild.addComponent(componentSystem.getNew<TileComponent>(tileToBuild, static_cast<TileComponent::Type>(tileType)));

	if (tileType != 0)
	{
		if (tileType != 9)
		{
			tileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(tileToBuild, 0.0f, 0.0f, (float)Constants::TILE_SIZE, (float)Constants::TILE_SIZE));
		}
		tileToBuild.addComponent(componentSystem.getNew<TileRenderer>(tileToBuild, tileSet, tileType - 1));
	}
	
	//replace TileRenderer with SpriteRenderer?
	/*if (tileType == 1)
	{
	}
	else if (tileType == 2)
	{
		tileToBuild.addComponent(componentSystem.getNew<TileRenderer>(tileToBuild, tileSet, 1));
		tileToBuild.addComponent(componentSystem.getNew<LiftTileComponent>(tileToBuild));
	}
	else if (tileType == 3)
	{
		tileToBuild.addComponent(componentSystem.getNew<TileRenderer>(tileToBuild, tileSet, 1));
		tileToBuild.addComponent(componentSystem.getNew<BurnTileComponent>(tileToBuild));
		tileToBuild.addComponent(componentSystem.getNew<DamageComponent>(tileToBuild, 2));
	}*/

	return tileToBuild;
}
