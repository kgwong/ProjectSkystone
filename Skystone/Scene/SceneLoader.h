#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <memory>
#include <map>
#include <string>

#include "Scene.h"

class SceneManager;
class LevelLoader;

class SceneLoader
{
public:
	static const std::string SCENE_FILEPATH_PREFIX;

public:
	SceneLoader();
	~SceneLoader();

	void setSceneManager(SceneManager* sceneManager);
	Scene* getSceneWithID(SceneID sceneID);

private:
	SceneManager* sceneManager_;
	LevelLoader* levelLoader_;

	std::map<SceneID, std::shared_ptr<Scene>> loadedScenes_;

private:
	bool sceneLoaded(SceneID sceneID);
	void load(SceneID sceneID);
	void loadObjects(SceneID, Scene* scene);
	std::string generateFilePath(SceneID sceneID);
	std::string sceneIDToString(SceneID sceneID);
};

#endif // SCENE_LOADER_H
