#include "ScrollingBackgroundBuilder.h"

#include "Components/Render/ScrollingSpriteRenderer.h"
#include "Resources/Resources.h"
#include <fstream>

ScrollingBackgroundBuilder::ScrollingBackgroundBuilder()
{
}


ScrollingBackgroundBuilder::~ScrollingBackgroundBuilder()
{
}

std::shared_ptr<GameObject> ScrollingBackgroundBuilder::build(ComponentSystem& componentSystem, const std::string& backgroundName)
{
	auto background = std::make_shared<GameObject>();
	auto& backgroundToBuild = *background;

	backgroundToBuild.setType(GameObject::Type::BACKGROUND);

	std::string spriteName;
	bool scrollx, scrolly;
	int layer;
	std::istringstream iss(backgroundName);

	iss >> spriteName >> std::boolalpha >> scrollx >> scrolly >> layer;
	SpriteSheet* spriteSheet = Resources::getSpriteSheet(spriteName);
	backgroundToBuild.addComponent(componentSystem.getNew<ScrollingSpriteRenderer>(backgroundToBuild, spriteSheet, layer, scrollx, scrolly));
	return background;
}
