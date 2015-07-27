#include "TileSet.h"

#include "SpriteSheet.h"

TileSet::TileSet(GameWindow* window, std::shared_ptr<SDL_Texture> texture, 
					SpritesheetInfo spritesheetInfo)
	: _window(window), _texture(texture), _numTiles(spritesheetInfo.num), _tileSize(spritesheetInfo.width)
{
	calculateSpriteLocations(_tiles, spritesheetInfo);
}

TileSet::~TileSet()
{
}

SDL_Texture* TileSet::getImage()
{
	return _texture.get();
}

SDL_Rect TileSet::getTile(int tileIndex)
{
	return _tiles[tileIndex];
}

Tile TileSet::createTile(int tileIndex, int x, int y)
{
	return Tile(_window, _texture.get(), _tiles[tileIndex], tileIndex, x, y, _tileSize);
}

int TileSet::getTileSize()
{
	return _tileSize;
}

int TileSet::getNumTiles()
{
	return _numTiles;
}