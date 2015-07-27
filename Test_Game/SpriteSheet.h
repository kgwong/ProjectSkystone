#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <vector>
#include <SDL/SDL.h>

#include "SpritesheetInfo.h"

void calculateSpriteLocations(std::vector<SDL_Rect>& locations, SpritesheetInfo spritesheetInfo);

#endif //SPRITESHEET_H