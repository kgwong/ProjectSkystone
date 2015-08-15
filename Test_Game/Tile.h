#ifndef TILE_H
#define TILE_H

#include "SDL/SDL.h"

#include "GameWindow.h"
#include "GameObject.h"
#include "ColliderComponent.h"

#include "TileType.h"
#include <memory>

class Tile : public GameObject
{
public:
	Tile() {}//
	Tile(GameWindow* window, SDL_Texture* tileSetImage, SDL_Rect tileRect, TileType tileType, int r, int c);
	~Tile();

	void update();
	void render();

	virtual EntityType getType() const;
	virtual Component* getComponent(ComponentType type);

	void onCollision(CollisionInfo& collision);

	TileType getTileType();

private:
	GameWindow* _window; 
	SDL_Texture* _tileSetImage;
	SDL_Rect _tileRect;
	SDL_Rect _drawDestination;

	TileType _tileType;

	std::shared_ptr<ColliderComponent> _colliderComponent;

};

#endif //TILE_H

