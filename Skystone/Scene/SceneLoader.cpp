#include "SceneLoader.h"

#include "SceneManager.h"
#include "Application/Path.h"
#include "Application/Log.h"
#include "Level/LevelManager.h"
#include "MainMenu.h"

#include <fstream>

const std::string SceneLoader::SCENE_FILEPATH_PREFIX = "Scenes/";

SceneLoader::SceneLoader()
{
	loadedScenes_.insert({SceneID::LEVEL, std::make_shared<LevelManager>()});
	loadMainMenu();
}

SceneLoader::~SceneLoader()
{
}

Scene* SceneLoader::getSceneWithID(SceneID sceneID)
{
	if (!sceneLoaded(sceneID))
		load(sceneID);
	return loadedScenes_.at(sceneID).get();
}

void SceneLoader::setSceneManager(SceneManager* sceneManager)
{
	sceneManager_ = sceneManager;
}

bool SceneLoader::sceneLoaded(SceneID sceneID)
{
	return loadedScenes_.find(sceneID) != loadedScenes_.end();
}

void SceneLoader::load(SceneID sceneID)
{
	if (sceneID == SceneID::LEVEL)
	{
		loadedScenes_.insert({sceneID, std::make_shared<LevelManager>()});
	}
	else
	{
		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		scene->setSceneManager(sceneManager_);
		
		loadObjects(sceneID, scene.get());
		loadedScenes_.insert({sceneID, scene});
	}
}

void SceneLoader::unload(SceneID sceneID)
{
	loadedScenes_.erase(sceneID);
}

void SceneLoader::loadObjects(SceneID sceneID, Scene* scene)
{
	std::string filepath = generateFilePath(sceneID);
	std::ifstream ifs(filepath);
	if (!ifs)
		LOG_STREAM(std::cerr) << "Failed to load: " << filepath;

	std::string line;
	std::string type, name;
	Point pos;

	while (getline(ifs, line))
	{
		std::istringstream iss(line);
		iss >> type >> name >> pos.x >> pos.y;
		scene->gameObjects.add(type, name, pos);
	}
}

void SceneLoader::loadMainMenu()
{
	std::shared_ptr<MainMenu> mainMenu = std::make_shared<MainMenu>();
	loadObjects(SceneID::MAIN_MENU, mainMenu.get());
	loadedScenes_.insert({SceneID::MAIN_MENU, mainMenu});
}

std::string SceneLoader::generateFilePath(SceneID sceneID)
{
	return Path::getFullPath(SceneLoader::SCENE_FILEPATH_PREFIX + sceneIDToString(sceneID));
}

std::string SceneLoader::sceneIDToString(SceneID sceneID)
{
	std::string result = "";
	switch (sceneID)
	{
		case SceneID::MAIN_MENU:
			result = "MainMenu";
			break;
		case SceneID::GAME_OVER:
			result = "GameOver";
			break;
		case SceneID::PAUSE:
			result = "Pause";
			break;
		default:
			break;
	}
	return result;
}