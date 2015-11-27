#include "ItemDropBuilder.h"

#include "Pickup.h"
#include "SpriteRenderer.h"
#include "TextureLoader.h"

#include <memory>

ItemDropBuilder::ItemDropBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}

ItemDropBuilder::~ItemDropBuilder()
{
}

Pickup& ItemDropBuilder::build(const std::string& itemName, Pickup& itemDropToBuild)
{
	itemDropToBuild.setRenderComponent(std::make_shared<SpriteRenderer>(textureLoader_->getTextureSheet("Assets/Pickups/pickup.png")));
	return itemDropToBuild;
}
