#include "TileSet.h"
#include "SpriteSheet.h"

TileSet::TileSet(GameWindow* window, const std::string& filepath, 
					int numTiles, int tileSize, 
					int tilesPerRow, int tilesPerColumn, 
					int padding)
	: _window(window), _numTiles(numTiles), _tileSize(tileSize)
{
	_image = loadTexture(window->renderer, filepath);
	
	calculateSpriteLocations(_tiles, numTiles, tileSize, tileSize, tilesPerRow, tilesPerColumn, padding);
}

TileSet::~TileSet()
{
	SDL_DestroyTexture(_image);
}

SDL_Texture* TileSet::getImage()
{
	return _image;
}

SDL_Rect TileSet::getTile(int tileIndex)
{
	return _tiles[tileIndex];
}

Tile TileSet::createTile(int tileIndex, int x, int y)
{
	return Tile(_window, _image, _tiles[tileIndex], tileIndex, x, y, _tileSize);
}

int TileSet::getTileSize()
{
	return _tileSize;
}

int TileSet::getNumTiles()
{
	return _numTiles;
}