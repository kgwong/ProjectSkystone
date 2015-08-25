#ifndef RESOURCE_LOCATOR_H
#define RESOURCE_LOCATOR_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

#include <unordered_map>
#include <string>
#include <memory>

#include "Errors.h"
#include "GameWindow.h"

#include "TextureSheet.h"

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

	TextureSheet* getTextureSheet(const std::string& basename);


	std::string getFullPath(const std::string& basename);
	std::shared_ptr<SDL_Texture> loadTexture(SDL_Renderer* renderer, const std::string& fullpath);

private:
	GameWindow* _gw;

	std::string _basePath;

	std::unordered_map<std::string, TextureSheet> _textureSheets;
};

#endif //RESOURCE_LOCATOR_H

