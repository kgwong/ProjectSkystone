#include "ItemDropBuilder.h"

#include "Components/Render/SpriteRenderer.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/ItemDrop/PickupComponent.h"

#include <memory>

ItemDropBuilder::ItemDropBuilder()
{
}

ItemDropBuilder::~ItemDropBuilder()
{
}

std::shared_ptr<GameObject> ItemDropBuilder::build(ComponentSystem& componentSystem, const std::string& itemName)
{
	auto newDrop = std::make_shared<GameObject>();
	auto& itemDropToBuild = *newDrop;
	itemDropToBuild.setType(GameObject::Type::DROP);
	itemDropToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(itemDropToBuild, "Assets/Pickups/pickup.png"));
	itemDropToBuild.addComponent(componentSystem.getNew<PhysicsComponent>(itemDropToBuild));
	itemDropToBuild.addComponent(componentSystem.getNew<ColliderComponent>(itemDropToBuild));
	itemDropToBuild.addComponent(componentSystem.getNew<PickupComponent>(itemDropToBuild));
	return newDrop;
}
