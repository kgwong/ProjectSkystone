#include "BackgroundBuilder.h"
#include "Components/Render/ScrollingSpriteRenderer.h"
#include "Resources/Resources.h"
#include <sstream>

BackgroundBuilder::BackgroundBuilder()
{
}


BackgroundBuilder::~BackgroundBuilder()
{
}

std::shared_ptr<GameObject> BackgroundBuilder::build(ComponentSystem& componentSystem, const std::string& backgroundName)
{
	std::istringstream iss(backgroundName);
	std::string filepath;
	bool scrollx, scrolly;
	int layer;
	iss >> filepath >> std::boolalpha >> scrollx >> scrolly >> layer;
	SpriteSheet* spriteSheet_ = Resources::getSpriteSheet(filepath);

	auto background = std::make_shared<GameObject>();
	auto& backgroundToBuild = *background;
	backgroundToBuild.setType(GameObject::Type::BACKGROUND);
	background->addComponent(componentSystem.getNew<ScrollingSpriteRenderer>(backgroundToBuild, spriteSheet_, layer, scrollx, scrolly));

	return background;
}