#include "TileBuilder.h"

#include "TextureLoader.h"
#include "GameConstants.h"
#include "ColliderComponent.h"
#include "SpriteRenderer.h"
#include "TileComponent.h"
#include "Liftcomponent.h"

TileBuilder::TileBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}


TileBuilder::~TileBuilder()
{
}

GameObject& TileBuilder::build(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild)
{
	tileToBuild.setType(GameObject::Type::TILE);
	TextureSheet* tileSet = textureLoader_->getTextureSheet("Assets/TileSets/bw.png");
	tileToBuild.addComponent(componentSystem.getNew<TileComponent>(tileToBuild, static_cast<TileComponent::Type>(tileType)));
	
	if (tileType == 1)
	{
		tileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(tileToBuild, tileSet, tileType));
		tileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(tileToBuild, 0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE));
	}
	else if (tileType == 2)
	{
		tileToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(tileToBuild, tileSet, 1));
		tileToBuild.addComponent(componentSystem.getNew<ColliderComponent>(tileToBuild, 0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE));
		tileToBuild.addComponent(componentSystem.getNew<LiftComponent>(tileToBuild));
	}
	return tileToBuild;
}
