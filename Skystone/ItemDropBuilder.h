#ifndef ITEM_DROP_BUILDER_H
#define ITEM_DROP_BUILDER_H

#include <string>

class Pickup;
class TextureLoader;

class ItemDropBuilder
{
public:
public:
	ItemDropBuilder(TextureLoader* textureLoader);
	~ItemDropBuilder();

	Pickup& build(const std::string& itemName, Pickup& itemDropToBuild);

private:
	TextureLoader* textureLoader_;
};

#endif //ITEM_DROP_BUILDER_H