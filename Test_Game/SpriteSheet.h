#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <vector>
#include <SDL/SDL.h>

void calculateSpriteLocations(std::vector<SDL_Rect>& locations, 
								int numSprites,
								int spriteWidth,
								int spriteHeight,
								int spritesPerRow,
								int spritesPerColumn,
								int padding);


#endif //SPRITESHEET_H