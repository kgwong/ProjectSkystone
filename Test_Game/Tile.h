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
	Tile(GameWindow* window, SDL_Texture* tileSetImage, SDL_Rect tileRect, int tileType, int r, int c, int size);
	~Tile();

	void update();
	void render();

	virtual EntityType getType() const;
	virtual Component* getComponent(ComponentType type);

public:
	int tileType; //should probably replace with enum or something more meaningful, rather than just an index

private:
	GameWindow* _window; 
	SDL_Texture* _tileSetImage;
	SDL_Rect _tileRect;
	SDL_Rect _drawDestination;

	ColliderComponent _colliderComponent;

};

#endif //TILE_H

