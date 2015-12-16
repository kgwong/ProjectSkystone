#ifndef TILE_BUILDER_H
#define TILE_BUILDER_H

class GameObject;

class TextureLoader;
class ComponentSystem;

class TileBuilder
{
public:
	TileBuilder(TextureLoader* textureLoader);
	~TileBuilder();

	GameObject& build(ComponentSystem& componentSystem, int tileType, GameObject& tileToBuild);

private:
	TextureLoader* textureLoader_;
};

#endif //TILE_BUILDER_H