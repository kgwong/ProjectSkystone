#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

#include <unordered_map>
#include <string>
#include <memory>

#include "Application/Errors.h"
#include "Application/GameWindow.h"

#include "SpriteSheet.h"

struct TextureDestroyer
{
	void operator()(SDL_Texture* texture) 
	{ 
		SDL_DestroyTexture(texture); 
	}
};

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	void initGameWindow(GameWindow* gameWindow);

	std::shared_ptr<SDL_Texture> loadTexture(const std::string& fullpath);

private:
	GameWindow* gameWindow_;
};

#endif //TEXTURE_LOADER_H

