#include "ResourceLocator.h"

#include "SpritesheetInfoReader.h"
#include "GameWindow.h"

ResourceLocator::ResourceLocator(GameWindow* gw)
	: _gw(gw)
{

	char* basePath = SDL_GetBasePath(); //SDL_GetBasePath() should only be called once

	std::string base = basePath;
	SDL_free(basePath);  

	base.pop_back();
	size_t pos = base.rfind('\\'); //
	_basePath = base.substr(0, pos) + '/';
}

ResourceLocator::~ResourceLocator()
{
}

std::string ResourceLocator::getFullPath(const std::string& basename)
{
	return _basePath + basename;	
}

std::shared_ptr<SDL_Texture> ResourceLocator::loadTexture(SDL_Renderer* renderer, const std::string& fullpath)
{
	std::cout << "Loading Texture: " << fullpath << std::endl; //

	SDL_Texture* texture = IMG_LoadTexture(renderer, fullpath.c_str());
	if (texture == nullptr)
		MySDL_Error("LoadTexture (" + fullpath + ")");
	return std::shared_ptr<SDL_Texture>(texture, TextureDestroyer());
}

TextureSheet* ResourceLocator::getTextureSheet(const std::string & basename)
{
	std::string fullpath = getFullPath(basename);

	if (_textureSheets.count(basename) == 0)
		_textureSheets.insert({ basename, TextureSheet(_gw, loadTexture(_gw->renderer, fullpath), SpritesheetInfoReader(fullpath).info()) });

	return &_textureSheets.at(basename);
}
