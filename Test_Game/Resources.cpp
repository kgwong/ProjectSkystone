#include "Resources.h"

std::string getAssetsPath(const std::string& path)
{
	char* basePath = SDL_GetBasePath(); //should only need to call once

	std::string base = basePath;
	SDL_free(basePath);

	base.pop_back();
	size_t pos = base.rfind('\\'); //
	base = base.substr(0, pos);


	return base + '/' + "Assets" + '/' + path;	
}

std::string getLevelsPath(const std::string& path) //temporary
{
	char* basePath = SDL_GetBasePath(); //should only need to call once

	std::string base = basePath;
	SDL_free(basePath);

	base.pop_back();
	size_t pos = base.rfind('\\'); //
	base = base.substr(0, pos);


	return base + '/' + "Levels" + '/' + path;	
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filepath)
{
	std::cout << "Loading Texture: " << getAssetsPath(filepath) << std::endl; //

	SDL_Texture* texture = IMG_LoadTexture(renderer, getAssetsPath(filepath).c_str());
	if (texture == nullptr)
		MySDL_Error("LoadTexture (" + filepath + ")");
	return texture;
}