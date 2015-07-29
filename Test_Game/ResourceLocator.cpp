#include "ResourceLocator.h"

#include "SpritesheetInfoReader.h"
#include "Sprite.h"

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


//lots of repeat here
Sprite* ResourceLocator::getSprite(const std::string& basename)
{
	std::string fullpath = getFullPath(basename);
	//better way to do this?
	if (_resources.count(fullpath) == 0)
		_resources.insert( std::make_pair( fullpath, Sprite(_gw, loadTexture(_gw->renderer, fullpath)) ) );
	return &_resources.at(fullpath);
}

Animation* ResourceLocator::getAnimation(const std::string& basename)
{
	std::string fullpath = getFullPath(basename);
	if (_animations.count(fullpath) == 0)
		_animations.insert( std::make_pair( fullpath, Animation( _gw, loadTexture(_gw->renderer, fullpath), SpritesheetInfoReader(fullpath).info() ) ) );
	return &_animations.at(fullpath);
}

TileSet* ResourceLocator::getTileSet(const std::string& basename)
{
	std::string fullpath = getFullPath(basename);
	if (_tileSets.count(fullpath) == 0)
		_tileSets.insert( std::make_pair( fullpath, TileSet( _gw, loadTexture(_gw->renderer, fullpath), SpritesheetInfoReader(fullpath).info() ) ) );
	return &_tileSets.at(fullpath);
}