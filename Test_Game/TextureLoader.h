#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

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

class TextureLoader
{
public:
	TextureLoader(GameWindow *gw);
	~TextureLoader();

	TextureSheet* getTextureSheet(const std::string& basename);

	std::shared_ptr<SDL_Texture> loadTexture(SDL_Renderer* renderer, const std::string& fullpath);

private:
	GameWindow* _gw;

	std::unordered_map<std::string, TextureSheet> _textureSheets;
};

#endif //TEXTURE_LOADER_H

