#include "ItemDropBuilder.h"

#include "Pickup.h"
#include "SpriteRenderer.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "TextureLoader.h"

#include <memory>

ItemDropBuilder::ItemDropBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}

ItemDropBuilder::~ItemDropBuilder()
{
}

Pickup& ItemDropBuilder::build(ComponentSystem& componentSystem, const std::string& itemName, Pickup& itemDropToBuild)
{
	itemDropToBuild.setType(ObjectType::DROP);
	itemDropToBuild.addComponent(componentSystem.getNewRenderer<SpriteRenderer>(itemDropToBuild, textureLoader_->getTextureSheet("Assets/Pickups/pickup.png")));
	itemDropToBuild.addComponent(componentSystem.getNewPhysics<PhysicsComponent>(itemDropToBuild));
	itemDropToBuild.addComponent(componentSystem.getNewNonUpdating<ColliderComponent>(itemDropToBuild));
	return itemDropToBuild;
}
