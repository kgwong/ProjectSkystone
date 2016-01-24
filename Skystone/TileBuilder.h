#ifndef TILE_BUILDER_H
#define TILE_BUILDER_H

class GameObject;

class ComponentSystem;

class TileBuilder
{
public:
	TileBuilder();
	~TileBuilder();

	GameObject& build(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild);
};

#endif //TILE_BUILDER_H