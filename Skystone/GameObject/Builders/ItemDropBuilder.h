#ifndef ITEM_DROP_BUILDER_H
#define ITEM_DROP_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class ComponentSystem;

class ItemDropBuilder
{
public:
	ItemDropBuilder();
	~ItemDropBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& itemName);
};

#endif //ITEM_DROP_BUILDER_H