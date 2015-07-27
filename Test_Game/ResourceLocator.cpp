#include "ResourceLocator.h"

#include "Sprite.h"

ResourceLocator::ResourceLocator(GameWindow* gw)
	: _gw(gw)
{
	char* basePath = SDL_GetBasePath(); //SDL_GetBasePath() should only be called once

	std::string base = basePath;
	SDL_free(basePath); 

	base.pop_back();
	size_t pos = base.rfind('\\'); //
	_assetsPath = base.substr(0, pos) + '/' + "Assets" + '/';

	std::shared_ptr<std::string> ptr(new std::string());

}


ResourceLocator::~ResourceLocator()
{
}

std::string ResourceLocator::getFullPath(const std::string& basename)
{
	return _assetsPath + basename;	
}

std::shared_ptr<SDL_Texture> ResourceLocator::loadTexture(SDL_Renderer* renderer, const std::string& basename)
{
	std::cout << "Loading Texture: " << getFullPath(basename) << std::endl; //

	SDL_Texture* texture = IMG_LoadTexture(renderer, getFullPath(basename).c_str());
	if (texture == nullptr)
		MySDL_Error("LoadTexture (" + basename + ")");
	return std::shared_ptr<SDL_Texture>(texture, TextureDestroyer());
}

Sprite* ResourceLocator::getSprite(const std::string& basename)
{
	//better way to do this?
	if (_resources.count(basename) == 0)
	{
		_resources.insert( std::make_pair( basename, Sprite(_gw, loadTexture(_gw->renderer, basename)) ) );
	}
	return &_resources.at(basename);
}

Animation* ResourceLocator::getAnimation(const std::string& basename)
{
	if (_animations.count(basename) == 0)
	{
		if (basename == "playerAnimation.png")//
			_animations.insert( std::make_pair( basename, Animation( _gw, loadTexture(_gw->renderer, basename), SpritesheetInfo(4, 30, 60, 4, 1) ) ) );
		else if (basename == "playerProjectile.png")
			_animations.insert( std::make_pair( basename, Animation( _gw, loadTexture(_gw->renderer, basename), SpritesheetInfo(2, 20, 10, 2, 1) ) ) );
	}
	return &_animations.at(basename);
}

TileSet* ResourceLocator::getTileSet(const std::string& basename)
{
	if (_tileSets.count(basename) == 0)
	{
		if (basename == "bw.png")//
			_tileSets.insert( std::make_pair( basename, TileSet( _gw, loadTexture(_gw->renderer, basename), SpritesheetInfo(2, 40, 40, 2, 1) ) ) );
	}
	return &_tileSets.at(basename);
}