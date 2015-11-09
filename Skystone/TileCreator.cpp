#include "TileCreator.h"

#include "TileType.h"


TileCreator::TileCreator()
{
}


TileCreator::~TileCreator()
{
}

Tile TileCreator::create(TextureSheet* textureSheet, int tileIndex, int r, int c)
{
	return Tile(new SpriteRenderer(textureSheet, tileIndex), 
			static_cast<TileType>(tileIndex), 
			r, c);
}
