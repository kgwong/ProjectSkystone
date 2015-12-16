#ifndef ITEM_DROP_BUILDER_H
#define ITEM_DROP_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class TextureLoader;
class ComponentSystem;

class ItemDropBuilder
{
public:
	ItemDropBuilder(TextureLoader* textureLoader);
	~ItemDropBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& itemName);

private:
	TextureLoader* textureLoader_;
};

#endif //ITEM_DROP_BUILDER_H