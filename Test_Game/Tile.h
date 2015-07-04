#ifndef TILE_H
#define TILE_H

#include "SDL/SDL.h"

#include "GameWindow.h"
#include "CollidingObject.h"

class Tile : public CollidingObject
{
public:
	Tile();
	Tile(GameWindow* window, SDL_Texture* tileSetImage, SDL_Rect tileRect, int tileType, int x, int y, int size);
	~Tile();

	void changeImage(SDL_Texture* newImage); //temp;
	void render();

public:
	int tileType; //should probably replace with enum or something more meaningful, rather than just an index

private:
	GameWindow* _window; 
	SDL_Texture* _tileSetImage;
	SDL_Rect _tileRect;
	SDL_Rect _drawDestination;

};

#endif //TILE_H

