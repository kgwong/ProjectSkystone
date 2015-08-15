#ifndef TILESET_H
#define TILESET_H

#include <memory>
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

	SDL_Texture* getTexture();
	SDL_Rect getTile(int tileIndex);
	Tile createTile(int tileIndex, int r, int c);

	int getNumTiles();

private:
	GameWindow* _window; //should probably change this later

	std::shared_ptr<SDL_Texture> _texture;
	std::vector<SDL_Rect> _tiles;

	int _numTiles;
};

#endif //TILESET_H

