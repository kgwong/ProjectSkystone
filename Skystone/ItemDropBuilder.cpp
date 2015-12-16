#include "ItemDropBuilder.h"

#include "SpriteRenderer.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "TextureLoader.h"
#include "PickupComponent.h"

#include <memory>

ItemDropBuilder::ItemDropBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
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
	itemDropToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(itemDropToBuild, textureLoader_->getTextureSheet("Assets/Pickups/pickup.png")));
	itemDropToBuild.addComponent(componentSystem.getNewPhysics<PhysicsComponent>(itemDropToBuild));
	itemDropToBuild.addComponent(componentSystem.getNewNonUpdating<ColliderComponent>(itemDropToBuild));
	itemDropToBuild.addComponent(componentSystem.getNewNonUpdating<PickupComponent>(itemDropToBuild));
	return newDrop;
}
