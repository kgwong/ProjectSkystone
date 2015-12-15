#ifndef TILE_H
#define TILE_H

#include "TileType.h"
#include <memory>

#include "GameObject.h"

class ColliderComponent;
class RenderComponent;

class Tile : public GameObject
{
public:
	Tile();
	Tile(Point position);
	Tile(int x, int y);
	~Tile();

	void update(Level& level);

	void onCollision(CollisionInfo& collision);

	TileType getTileType();
	void setTileType(int tileType);

private:
	TileType _tileType;
};

#endif //TILE_H

