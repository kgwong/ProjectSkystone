#include "TileBuilder.h"

#include "TextureLoader.h"
#include "GameConstants.h"
#include "ColliderComponent.h"
#include "SpriteRenderer.h"

#include "Tile.h"

TileBuilder::TileBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}


TileBuilder::~TileBuilder()
{
}

Tile& TileBuilder::build(ComponentSystem& componentSystem, int tileType, Tile& tileToBuild)
{
	tileToBuild.setType(ObjectType::TILE);
	TextureSheet* tileSet = textureLoader_->getTextureSheet("Assets/TileSets/bw.png");
	tileToBuild.setTileType(tileType);

	if (tileType == 1)
	{
		tileToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(tileToBuild, tileSet, tileType));
		tileToBuild.addComponent(componentSystem.getNewNonUpdating<ColliderComponent>(tileToBuild, 0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE));
	}

	return tileToBuild;
}
