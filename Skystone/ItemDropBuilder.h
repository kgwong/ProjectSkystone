#ifndef ITEM_DROP_BUILDER_H
#define ITEM_DROP_BUILDER_H

#include <string>

class Pickup;
class TextureLoader;
class ComponentSystem;

class ItemDropBuilder
{
public:
	ItemDropBuilder(TextureLoader* textureLoader);
	~ItemDropBuilder();

	Pickup& build(ComponentSystem& componentSystem, const std::string& itemName, Pickup& itemDropToBuild);

private:
	TextureLoader* textureLoader_;
};

#endif //ITEM_DROP_BUILDER_H