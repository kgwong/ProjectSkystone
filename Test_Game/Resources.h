#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Errors.h"

std::string getAssetsPath(const std::string& path);//
std::string getLevelsPath(const std::string& path);//

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filepath);

#endif //RESOURCES_H