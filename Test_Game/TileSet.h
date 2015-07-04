#ifndef TILESET_H
#define TILESET_H

#include <vector>

#include "GameWindow.h"
#include "Resources.h"
#include "Tile.h"

class TileSet
{
public:
	TileSet(GameWindow* window, const std::string& filepath, 
			int numTiles, int tileSize, 
			int tilesPerRow, int tilesPerColumn, 
			int padding = 0);
	~TileSet();

	SDL_Texture* getImage();
	SDL_Rect getTile(int tileIndex);
	Tile createTile(int tileIndex, int x, int y);

	int getTileSize();
	int getNumTiles();

private:
	GameWindow* _window; //should probably change this later

	SDL_Texture* _image;
	std::vector<SDL_Rect> _tiles;

	int _numTiles;

	int _tileSize; //square tiles, please
};

#endif //TILESET_H

