#include "TextureLoader.h"

#include "SpritesheetInfoReader.h"
#include "GameWindow.h"

#include "Path.h"
#include "Log.h"

TextureLoader::TextureLoader(GameWindow* gameWindow)
	: gameWindow_(gameWindow)
{
}

TextureLoader::~TextureLoader()
{
}

std::shared_ptr<SDL_Texture> TextureLoader::loadTexture(SDL_Renderer* renderer, const std::string& fullpath)
{
	LOG_COUT << "Loading Texture: " << fullpath;

	SDL_Texture* texture = IMG_LoadTexture(renderer, fullpath.c_str());

	if (texture == nullptr)
		MySDL_Error("LoadTexture (" + fullpath + ")");
	return std::shared_ptr<SDL_Texture>(texture, TextureDestroyer());
}

TextureSheet* TextureLoader::getTextureSheet(const std::string& basename)
{
	std::string fullpath = Path::getFullPath(basename);

	if (textureSheets_.count(basename) == 0)
		textureSheets_.insert({ basename, TextureSheet(gameWindow_, loadTexture(gameWindow_->getRenderer(), fullpath), SpritesheetInfoReader(fullpath).info()) });
	
	return &textureSheets_.at(basename);
}
