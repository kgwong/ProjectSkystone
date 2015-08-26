#include "Path.h"

#include <SDL/SDL.h>

#include <iostream>

std::string Path::basePath = "";

void Path::initBasePath()
{
	if (basePath.empty()) //only run if not initialized
	{
		char* base = SDL_GetBasePath(); //SDL_GetBasePath() should only be called once
		basePath = base;
		SDL_free(base);

		basePath.pop_back();
		size_t pos = basePath.rfind('\\'); //
		basePath = basePath.substr(0, pos) + '/';
	}
}

std::string Path::getBasePath()
{
	initBasePath();
	return basePath;
}

std::string Path::getFullPath(std::string relativePath)
{
	initBasePath();
	return basePath + relativePath;
}
