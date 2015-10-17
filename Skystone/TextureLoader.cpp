#include "TextureLoader.h"

#include "SpritesheetInfoReader.h"
#include "GameWindow.h"

#include "Path.h"
#include "Log.h"

TextureLoader::TextureLoader(GameWindow* gw)
	: _gw(gw)
{
}

TextureLoader::~TextureLoader()
{
}

std::shared_ptr<SDL_Texture> TextureLoader::loadTexture(SDL_Renderer* renderer, const std::string& fullpath)
{
	LOG << "Loading Texture: " << fullpath;

	SDL_Texture* texture = IMG_LoadTexture(renderer, fullpath.c_str());
	if (texture == nullptr)
		MySDL_Error("LoadTexture (" + fullpath + ")");
	return std::shared_ptr<SDL_Texture>(texture, TextureDestroyer());
}

TextureSheet* TextureLoader::getTextureSheet(const std::string& basename)
{
	std::string fullpath = Path::getFullPath(basename);

	if (_textureSheets.count(basename) == 0)
		_textureSheets.insert({ basename, TextureSheet(_gw, loadTexture(_gw->getRenderer(), fullpath), SpritesheetInfoReader(fullpath).info()) });

	return &_textureSheets.at(basename);
}
