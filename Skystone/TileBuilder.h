#ifndef TILE_BUILDER_H
#define TILE_BUILDER_H

class Tile;

class TextureLoader;
class ComponentSystem;

class TileBuilder
{
public:
	TileBuilder(TextureLoader* textureLoader);
	~TileBuilder();

	Tile& build(ComponentSystem& componentSystem, int tileType, Tile& tileToBuild);

private:
	TextureLoader* textureLoader_;
};

#endif //TILE_BUILDER_H