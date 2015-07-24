#ifndef TILE_H
#define TILE_H

#include "SDL/SDL.h"

#include "GameWindow.h"
#include "GameObject.h"
#include "ColliderComponent.h"

class Tile : public GameObject
{
public:
	Tile();
	Tile(GameWindow* window, SDL_Texture* tileSetImage, SDL_Rect tileRect, int tileType, int x, int y, int size);
	~Tile();

	void update();
	void changeImage(SDL_Texture* newImage); //temp;
	void render();

	virtual EntityType getType();

public:
	int tileType; //should probably replace with enum or something more meaningful, rather than just an index
	ColliderComponent _colliderComponent;

private:
	GameWindow* _window; 
	SDL_Texture* _tileSetImage;
	SDL_Rect _tileRect;
	SDL_Rect _drawDestination;



};

#endif //TILE_H

