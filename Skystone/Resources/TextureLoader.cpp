#include "TextureLoader.h"

#include "GameWindow.h"

#include "Path.h"
#include "Log.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

void TextureLoader::initGameWindow(GameWindow* gameWindow)
{
	gameWindow_ = gameWindow;
}

std::shared_ptr<SDL_Texture> TextureLoader::loadTexture(const std::string& fullpath)
{
	LOG_COUT << "Loading Texture: " << fullpath;

	SDL_Texture* texture = IMG_LoadTexture(gameWindow_->getRenderer(), fullpath.c_str());

	if (texture == nullptr)
		MySDL_Error("LoadTexture (" + fullpath + ")");
	return std::shared_ptr<SDL_Texture>(texture, TextureDestroyer());
}