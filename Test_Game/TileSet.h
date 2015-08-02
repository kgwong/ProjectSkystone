#ifndef TILESET_H
#define TILESET_H

#include <vector>

#include "GameWindow.h"
#include "Tile.h"
#include "SpritesheetInfo.h"


class TileSet
{
public:
	TileSet(GameWindow* window, std::shared_ptr<SDL_Texture> texture, 
			SpritesheetInfo spritesheetInfo);
	~TileSet();

	SDL_Texture* getImage();
	SDL_Rect getTile(int tileIndex);
	Tile createTile(int tileIndex, int r, int c);

	int getTileSize();
	int getNumTiles();

private:
	GameWindow* _window; //should probably change this later

	std::shared_ptr<SDL_Texture> _texture;
	std::vector<SDL_Rect> _tiles;

	int _numTiles;

	int _tileSize; //square tiles, please
};

#endif //TILESET_H

