#ifndef RESOURCE_LOCATOR_H
#define RESOURCE_LOCATOR_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

#include <unordered_map>
#include <string>
#include <memory>

#include "Errors.h"

#include "Sprite.h"
#include "Animation.h"
#include "TileSet.h"

#include "SpritesheetInfo.h"

struct TextureDestroyer
{
	void operator()(SDL_Texture* texture) 
	{ 
		SDL_DestroyTexture(texture); 
	}
};

class ResourceLocator
{
public:
	ResourceLocator(GameWindow *gw);
	~ResourceLocator();

	Sprite* getSprite(const std::string& basename);
	Animation* getAnimation(const std::string& basename);
	TileSet* getTileSet(const std::string& basename);

	std::string getFullPath(const std::string& basename);
	std::shared_ptr<SDL_Texture> loadTexture(SDL_Renderer* renderer, const std::string& fullpath);

private:
	GameWindow* _gw;

	std::string _basePath;

	std::unordered_map<std::string, Sprite> _resources; 
	std::unordered_map<std::string, Animation> _animations;
	std::unordered_map<std::string, TileSet> _tileSets;
};

#endif //RESOURCE_LOCATOR_H

