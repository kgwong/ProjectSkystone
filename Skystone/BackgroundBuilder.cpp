#include "BackgroundBuilder.h"
#include "Components/Render/SpriteRenderer.h"
#include "Components/Render/ScrollingSpriteRenderer.h"
#include "Resources/Resources.h"
#include <fstream>
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
	std::string firstWord;
	iss >> firstWord;
	std::shared_ptr<GameObject> background;

	if (firstWord != "Scrolling")
	{
		background = buildStaticBackground(componentSystem, backgroundName);
	}
	else
	{
		background = buildScrollingBackground(componentSystem, iss);
	}
	return background;
}

std::shared_ptr<GameObject> BackgroundBuilder::buildStaticBackground(ComponentSystem& componentSystem, const std::string& backgroundName)
{
	auto background = std::make_shared<GameObject>();
	auto& backgroundToBuild = *background;
	backgroundToBuild.setType(GameObject::Type::BACKGROUND);
	SpriteSheet* spriteSheet = nullptr;

	// really ought to sort out where .pngs should go, but for now check both
	std::string assets = "Assets/" + backgroundName + ".png";
	std::string images = "Images/" + backgroundName + ".png";

	if(backgroundExists(assets))
	{
		spriteSheet = Resources::getSpriteSheet(assets);
	}
	else if (backgroundExists(images))
	{

		spriteSheet = Resources::getSpriteSheet(images);
	}
	else
	{
		LOG("Warning") << "Invalid static background name: " << backgroundName << ", no static background added";
	}
	backgroundToBuild.addComponent(componentSystem.getNew<SpriteRenderer>(backgroundToBuild, spriteSheet));
	return background;
}

std::shared_ptr<GameObject> BackgroundBuilder::buildScrollingBackground(ComponentSystem& componentSystem, std::istringstream& iss)
{
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

bool BackgroundBuilder::backgroundExists(const std::string& relPath)
{
	std::string fullpath = Path::getFullPath(relPath);
	std::ifstream testFile(fullpath);
	return testFile.good();
}