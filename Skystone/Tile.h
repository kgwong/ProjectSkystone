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
	void render(Level& level);

	virtual EntityType getType() const;
	void onCollision(CollisionInfo& collision);

	TileType getTileType();
	void setTileType(int tileType);

	void setRenderComponent(std::shared_ptr<RenderComponent> renderComponent);
	void setColliderComponent(std::shared_ptr<ColliderComponent> colliderComponent);

private:
	TileType _tileType;//

	std::shared_ptr<RenderComponent> renderComponent_;
	std::shared_ptr<ColliderComponent> colliderComponent_;

};

#endif //TILE_H

