#include "TileBuilder.h"

#include "TextureLoader.h"
#include "GameConstants.h"

TileBuilder::TileBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}


TileBuilder::~TileBuilder()
{
}

Tile* TileBuilder::build(int tileType, Tile& tileToBuild)
{
	TextureSheet* tileSet = textureLoader_->getTextureSheet("Assets/TileSets/bw.png");
	tileToBuild.setRenderComponent(std::shared_ptr<RenderComponent>(new SpriteRenderer(tileSet, tileType)));
	tileToBuild.setTileType(tileType);

	if (tileType == 1)
	{
		tileToBuild.setColliderComponent(std::shared_ptr<ColliderComponent>(new ColliderComponent(0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE)));
	}

	return &tileToBuild;
}
